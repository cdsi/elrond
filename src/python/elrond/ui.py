from __future__ import division
from __future__ import with_statement

import os
import thread
import threading
import time

from configobj import ConfigObj

import gobject
import gtk

from elrond.concurrent import Task
from elrond.util import Object

class Chooser(gtk.FileChooserDialog):

        def __init__(self):
                buttons = (gtk.STOCK_CANCEL, gtk.RESPONSE_CANCEL, gtk.STOCK_OPEN, gtk.RESPONSE_OK)
                gtk.FileChooserDialog.__init__(self, title=None, action=gtk.FILE_CHOOSER_ACTION_OPEN,
                                               buttons=buttons)

class Widget(Object):

        def get_filename(self, option, default):
                chooser = Chooser()

                widget = self.builder.get_object(option)

                target = widget.get_text()
                if len(target) == 0:
                        target = '.PHONY'

                path = os.path.dirname(target)
                if len(path) == 0:
                        target = default + os.sep + target

                chooser.set_filename(target)

                response = chooser.run()
                if response == gtk.RESPONSE_OK:
                        widget.set_text(chooser.get_filename())

                chooser.destroy()

        def toggle(self, key, value):
                widget = self.builder.get_object(key)
                widget.set_sensitive(value)

                if value == True:
                        return

                try:
                        widget.set_active(False)
                        widget.toggled()
                except:
                        pass

        # This pertains to a treeview/liststore with the checkbox set as userdata
        # (passed in as the widget parameter).
        def on_toggled(self, widget, index):
                i = widget.get_iter(index)
                widget.set(i, 1, not widget.get_value(i, 1))

        def on_changed(self, widget):
                section, key = widget.get_name().split("__")
                
                value = None

                # order is important...
                attrs = [
                        'get_text',
                        'get_active_text',
                        'get_active',
                ]

                for attr in attrs:
                        if hasattr(widget, attr):
                                value = getattr(widget, attr)()
                                break

                if value is not None:
                        self.prefs[section][key] = value
                        self.prefs.write()
                else:
                        print 'ERROR! Unable to get value of %s' % (type(widget))

        def draw(self):
                while gtk.events_pending():
                        gtk.main_iteration()

        def spin(self, interval=1):
                while True:
                        self.draw()
                        time.sleep(interval)
                        yield

        def show(self):
                self.widget.show()

        def hide(self):
                self.widget.hide()

        def run(self):
                gtk.main()
                
        def exit(self):
                gtk.main_quit()
                thread.exit()

        def on_draw(self, widget):
                self.draw()

        def on_show(self, widget):
                self.show()

        def on_hide(self, widget):
                self.hide()

        def on_run(self, widget):
                self.run()

        def on_exit(self, widget):
                self.exit()

        def loadui(self, path, name):
                self.builder = gtk.Builder()
                self.builder.add_from_file(path + os.sep + name + '.ui')
                self.builder.connect_signals(self)

                self.widget = self.builder.get_object(name)

        def loaddb(self, path, name):
                self.prefs = ConfigObj(path + os.sep + name + '.ini')

                for section in self.prefs.keys():
                        for key, value in self.prefs[section].items():
                                try:
                                        widget = self.builder.get_object(section + '__' + key)

                                        if type(widget) == gtk.CheckButton:
                                                widget.set_active(self.to_bool(value))

                                        if type(widget) == gtk.ComboBox:
                                                model = widget.get_model()
                                                i = [row[0] for row in model].index(value)
                                                widget.set_active(i)

                                        if type(widget) == gtk.Entry:
                                                widget.set_text(value)

                                        if type(widget) == gtk.RadioButton:
                                                widget.set_active(self.to_bool(value))

                                        if type(widget) == gtk.SpinButton:
                                                widget.set_value(float(value))

                                        widget.toggled()
                                except:
                                        pass

        def __init__(self):
                gobject.threads_init()

class Console(Widget):

        def clear(self):
                self.__buffer.set_text('')
                self.draw()

        def on_clear(self, widget):
                self.clear()

        def append(self, text):
                # end_iter is updated by the draw calls so don't attempt to re-use it...

                self.__buffer.insert(self.__buffer.get_end_iter(), text)
                self.draw()

                self.__textview.scroll_to_iter(self.__buffer.get_end_iter(), 0)
                self.draw()

        def appendln(self, text):
                self.append(text + "\n")

        def write(self, text):
                self.clear()
                self.append(text)

        def writeln(self, text):
                self.write(text + "\n")

        def __init__(self):
                Widget.__init__(self)

                path = os.environ['ELROND_ETC']
                name = 'console'

                self.loadui(path, name)
                self.loaddb(path, name)

                self.__textview = self.builder.get_object('textview')
                self.__buffer = self.__textview.get_buffer()

class Dialog(Widget):

        @apply
        def labels():

                def fget(self):
                        return self.__labels

                def fset(self, value):
                        self.__labels = value
                        labels = self.__labels.split(':')

                        self.__table = self.builder.get_object('table')
                        self.__table.resize(len(labels), 2)

                        self.__entries = []

                        for i, text in enumerate(labels):
                                label = gtk.Label(text + ':')
                                label.set_justify(gtk.JUSTIFY_LEFT)
                                label.show()

                                self.__table.attach(label, 0, 1, i, i + 1)

                                entry = gtk.Entry()
                                entry.set_editable(False)
                                entry.show()

                                self.__entries.append(entry)

                                self.__table.attach(entry, 1, 2, i, i + 1)

                def fdel(self):
                        del self.__labels

                return property(**locals())

        def __play(self):
                while self.__running:
                        try:
                                with open(self.socket, 'r') as fd:
                                        while self.__running:
                                                # TODO: readline needs a timeout
                                                line = fd.readline()
                                                print 'something... anything...'
                                                if line == '':
                                                        break

                                                data = line.strip().split(':')

                                                for i, text in enumerate(data):
                                                        if text == '':
                                                                continue

                                                        entry = self.__entries[i]
                                                        entry.set_text(text)

                                                self.draw()

                                                yield
                        except:
                                pass

        def play(self):
                if self.__running:
                        return

                self.__running = True
                self.__task.start()

        def stop(self):
                self.__running = False
                self.__task.stop()

        def kill(self):
                self.stop()
                self.__task.kill()

        def __init__(self):
                Widget.__init__(self)

                path = os.environ['ELROND_ETC']
                name = 'dialog'

                self.loadui(path, name)
                self.loaddb(path, name)

                gtk.quit_add(0, self.kill)

                self.__task = Task(self.__play)
                self.stop()

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
