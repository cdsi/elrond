from __future__ import division
from __future__ import with_statement

import os
import thread
import threading
import time

from configobj import ConfigObj

import gobject
import gtk

from elrond.util import Object

class Task(Object):
        """http://unpythonic.blogspot.com/2007/08/using-threads-in-pygtk.html
        """

        def __loop(self, rc):
                if rc is None:
                        rc = ()
                if not isinstance(rc, tuple):
                        rc = (rc,)
                self.callback(*rc)

        def __start(self, *args, **kwargs):
                for rc in self.generator(*args, **kwargs):
                        if self.callback is not None:
                                gobject.idle_add(self.__loop, rc)
                if self.complete is not None:
                        gobject.idle_add(self.complete)

        def start(self, *args, **kwargs):
                if self.__running:
                        return

                self.__running = True
                thread = threading.Thread(target=self.__start, args=args, kwargs=kwargs)
                thread.start()

        def stop(self):
                if not self.__running:
                        return

                self.__running = False

        def kill(self):
                self.stop()
                thread.exit()

        def __init__(self, generator, callback=None, complete=None):
                self.generator = generator
                self.callback = callback
                self.complete = complete

                self.__running = False

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

        def on_toggled(self, widget, index):
                i = widget.get_iter(index)
                widget.set(i, 1, not widget.get_value(i, 1))

        def on_changed(self, widget):
                section, key = widget.get_name().split("__")

                try:
                        value = widget.get_text()
                except:
                        try:
                                value = widget.get_active()
                        except:
                                print 'ERROR! Unable to get value of %s' % (type(widget))

                self.props[section][key] = value

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
                self.props = ConfigObj(path + os.sep + name + '.ini')

                for section in self.props.keys():
                        for key, value in self.props[section].items():
                                try:
                                        widget = self.builder.get_object(section + '__' + key)

                                        if type(widget) == gtk.CheckButton:
                                                widget.set_active(self.to_bool(value))

                                        if type(widget) == gtk.ComboBox:
                                                widget.set_active(int(value))

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

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
