from __future__ import division
from __future__ import with_statement

import math
import os
import thread
import time

import gtk
import pango

from elrond.tasks import Task
from elrond.util import Object, Preferences, Property

class Chooser(gtk.FileChooserDialog):

        def __init__(self):
                buttons = (gtk.STOCK_CANCEL, gtk.RESPONSE_CANCEL, gtk.STOCK_OPEN, gtk.RESPONSE_OK)
                gtk.FileChooserDialog.__init__(self, title=None, action=gtk.FILE_CHOOSER_ACTION_OPEN,
                                               buttons=buttons)

class Colors(Object):

        BLACK = gtk.gdk.Color(red=0x0000, green=0x0000, blue=0x0000)
        WHITE = gtk.gdk.Color(red=0xFFFF, green=0xFFFF, blue=0xFFFF)
        RED = gtk.gdk.Color(red=0xFFFF, green=0x0000, blue=0x0000)
        GREEN = gtk.gdk.Color(red=0x0000, green=0xFFFF, blue=0x0000)
        BLUE = gtk.gdk.Color(red=0x0000, green=0xFFFF, blue=0xFFFF)
        YELLOW = gtk.gdk.Color(red=0xFFFF, green=0xFFFF, blue=0x0000)

        SUCCESS = GREEN
        WARNING = YELLOW
        ERROR = RED

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

                if value:
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
                # https://bugzilla.gnome.org/show_bug.cgi?id=591085#c19
                try:
                        section, key = widget.get_name().split("__")
                except:
                        section, key = gtk.Buildable.get_name(widget).split("__")
                
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

        def spin(self, interval=1):
                while True:
                        self.draw()
                        time.sleep(interval)
                        yield

        def draw(self):
                while gtk.events_pending():
                        gtk.main_iteration()

        def show(self):
                self.widget.show()
                if self.__subwidget:
                        self.__subwidget.show()

        def hide(self):
                self.widget.hide()
                if self.__subwidget:
                        self.__subwidget.hide()

        def run(self):
                gtk.main()
                
        def delete(self):
                if self.__subwidget:
                        self.__subwidget.delete()

        def exit(self):
                if self.embedded:
                        self.hide()
                else:
                        gtk.main_quit()
                        try:
                                thread.exit()
                        except SystemExit:
                                pass
                        finally:
                                self.delete()
                                
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

                if self.__subwidget:
                        container = self.builder.get_object('container')
                        container.add(self.__subwidget.widget)

        def loaddb(self, path, name):
                self.prefs = Preferences(path + os.sep + name + '.ini')

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

                                        if type(widget) == gtk.ToggleToolButton:
                                                widget.set_active(self.to_bool(value))

                                        widget.toggled()
                                except:
                                        pass

        @Property
        def title():
                """Allow applications to get/set the widget title."""

                def fget(self):
                        return self.__title

                def fset(self, title):
                        self.__title = title

                        try:
                                self.widget.set_title(self.__title)
                        except:
                                pass

                return locals()

        @Property
        def deletable():
                """Allow applications to remove the close button on windows."""

                def fget(self):
                        return self.__deletable

                def fset(self, deletable):
                        self.__deletable = self.to_bool(deletable)

                        try:
                                # TODO:
                                self.widget.set_deletable(self.__deletable)
                        except:
                                pass

                return locals()

        @Property
        def mode():
                """Controls which UI widgets are shown."""

                def fget(self):
                        return self.__mode

                def fset(self, mode):
                        self.__mode = mode

                        widgets = self.builder.get_objects()

                        if self.__mode == 'expert':
                                expert = True
                                novice = False

                        if self.__mode == 'novice':
                                expert = False
                                novice = True

                        for widget in widgets:
                                if not hasattr(widget, 'name'):
                                        continue

                                name = widget.name

                                if name.endswith('expert'):
                                        if not expert:
                                                widget.hide()

                                if name.endswith('novice'):
                                        if not novice:
                                                widget.hide()

                return locals()

        def __init__(self, widget=None):
                gtk.gdk.threads_init()

                self.__subwidget = widget

                self.__title = None

                self.embedded = False

class Window(Widget):

        def __init__(self, *args, **kwargs):
                Widget.__init__(self, *args, **kwargs)

                path = os.environ['ELROND_ETC']
                name = 'elrond-window'

                self.loadui(path, name)
                self.loaddb(path, name)

class SaveAs(Widget):

        def get_selection(self, path=None, filename=None):
                if filename is None:
                        filename = '.PHONY'

                if path is not None:
                        filename = path + os.sep + filename

                self.widget.set_filename(filename)

                self.show()

        def __callback(self, filename):
                if self.callback is not None:
                        self.callback(filename)

        def on_cancel(self, widget):
                self.__callback(None)

        def on_ok(self, widget):
                self.__callback(self.widget.get_filename())

        def __init__(self, *args, **kwargs):
                Widget.__init__(self, *args, **kwargs)

                path = os.environ['ELROND_ETC']
                name = 'elrond-saveas'

                self.loadui(path, name)
                self.loaddb(path, name)

                self.callback = None

class YesNo(Widget):

        def get_answer(self, question):
                widget = self.builder.get_object('textview')
                widget.modify_font(pango.FontDescription('monospace 12'))

                widget = self.builder.get_object('textbuffer')
                widget.set_text(question)

                widget = self.builder.get_object('yes-button')
                widget.grab_focus()

                self.show()

        def __callback(self, answer):
                if self.callback is not None:
                        self.callback(answer)

        def on_no(self, widget):
                self.__callback(False)

        def on_yes(self, widget):
                self.__callback(True)

        def __init__(self, *args, **kwargs):
                Widget.__init__(self, *args, **kwargs)

                path = os.environ['ELROND_ETC']
                name = 'elrond-yesno'

                self.loadui(path, name)
                self.loaddb(path, name)

                self.callback = None

class Playable(Widget):

        def play(self, *args, **kwargs):
                if self.__is_running:
                        raise

                self.__task = Task(self.__tasklette)

                self.__is_running = True
                self.__task.start(*args, **kwargs)

        def stop(self):
                self.__is_running = False
                self.__task.stop()

        def kill(self):
                self.stop()
                self.__task.kill()

        def __init__(self, tasklette):
                Widget.__init__(self)

                gtk.quit_add(0, self.kill)

                self.__tasklette = tasklette
                self.__is_running = False

class Console(Playable):

        def append(self, text):
                # end_iter is updated by the draw calls so don't attempt to re-use it...

                self.__buffer.insert(self.__buffer.get_end_iter(), text)
                self.draw()

                self.__textview.scroll_to_mark(self.__buffer.get_insert(), 0)
                self.draw()

        def appendln(self, text):
                self.append(text + "\n")

        def write(self, text):
                self.clear()
                self.append(text)

        def writeln(self, text):
                self.write(text + "\n")

        def __save(self, filename):
                if filename is None:
                        return

                self.__filename = filename

                with open(self.__filename, 'w') as fd:
                        fd.write(self.__buffer.get_text(*self.__buffer.get_bounds()))

        def on_save(self, widget):
                if self.__filename is None:
                        self.__chooser.get_selection()
                else:
                        self.__save(self.__filename)

        def on_saveas(self, widget):
                self.__chooser.get_selection(filename=self.__filename)

        def clear(self):
                self.__buffer.set_text('')
                self.draw()

        def on_clear(self, widget):
                self.clear()

        def __tasklette(self, producer):
                for line in producer():
                        gtk.gdk.threads_enter()

                        try:
                                self.append(line)
                        except:
                                continue
                        finally:
                                gtk.gdk.threads_leave()

        def __init__(self):
                Playable.__init__(self, self.__tasklette)

                path = os.environ['ELROND_ETC']
                name = 'elrond-console'

                self.loadui(path, name)
                self.loaddb(path, name)

                self.__textview = self.builder.get_object('textview')
                self.__buffer = self.__textview.get_buffer()

                self.__chooser = SaveAs()
                self.__chooser.deletable = False
                self.__chooser.embedded = True
                self.__chooser.callback = self.__save

                self.__filename = None

                self.__textview.modify_font(pango.FontDescription('monospace 12'))

class Dialog(Playable):

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

        def __tasklette(self, producer):
                for line in producer():
                        data = line.strip().split(':')

                        for i, text in enumerate(data):
                                if text == '':
                                        continue

                                gtk.gdk.threads_enter()

                                try:
                                        entry = self.__entries[i]
                                        entry.set_text(text)
                                except:
                                        continue
                                finally:
                                        gtk.gdk.threads_leave()

        def __init__(self):
                Playable.__init__(self, self.__tasklette)

                path = os.environ['ELROND_ETC']
                name = 'elrond-dialog'

                self.loadui(path, name)
                self.loaddb(path, name)

class Plane(Widget):

        def plot(self, x, y, z, color='white', name=None, text=None, vector=None):
                x_limit = 40000
                y_limit = 40000

                # TODO:
                z_pixel = 15

                x_scale = abs(self.__w / x_limit)
                x_pixel = int(self.__w_half + (x * x_scale)) - int(z_pixel / 2)

                y_scale = abs(self.__h / y_limit)
                y_pixel = int(self.__h_half - (y * y_scale)) - int(z_pixel / 2)

                gc = self.__drawingarea.window.new_gc()
                gc.set_foreground(gc.get_colormap().alloc_color(color))

                self.__pixmap.draw_arc(gc, True, x_pixel, y_pixel, z_pixel, z_pixel, 0, 360 * 64)

                gc = self.__drawingarea.get_style().fg_gc[gtk.STATE_NORMAL]

                if not name == None:
                        self.__layout.set_text(name)
                        self.__pixmap.draw_layout(gc, x_pixel, y_pixel + z_pixel, self.__layout)
                        text = '%s: (%d,%d) %s' % (name, x, y, text)

                if not text == None:
                        self.__layout.set_text(text)
                        self.__pixmap.draw_layout(gc, self.__legend_x, self.__legend_y, self.__layout)
                        self.__legend_y -= 20 # TODO: text height in pixels

                if not vector == None:
                        x_center = x_pixel + int(z_pixel / 2)
                        y_center = y_pixel + int(z_pixel / 2)
                        x_vector = int(x_center + (vector[0] * x_scale * 10))
                        y_vector = int(y_center - (vector[1] * y_scale * 10))
                        self.__pixmap.draw_line(gc, x_center, y_center, x_vector, y_vector)

                self.__drawingarea.queue_draw()
                self.draw()

        def saveas(self):
                pass

        def on_saveas(self, widget):
                self.saveas()

        def clear(self):
                self.__drawingarea.queue_resize()

        def on_clear(self, widget):
                self.clear()

        def on_drawingarea_configure_event(self, widget, event):
                x, y, self.__w, self.__h = widget.get_allocation()

                # keep drawingarea square...

                if self.__w > self.__h:
                        self.__w = self.__h
                else:
                        self.__h = self.__w

                self.__w_half = int(self.__w / 2)
                self.__h_half = int(self.__h / 2)

                self.__legend_x = 15
                self.__legend_y = self.__h - 25

                self.__pixmap = gtk.gdk.Pixmap(widget.window, self.__w, self.__h)

                # draw grid...

                gc = widget.get_style().white_gc
                self.__pixmap.draw_rectangle(gc, True, 0, 0, self.__w, self.__h)

                gc = self.__drawingarea.window.new_gc()
                gc.set_foreground(gc.get_colormap().alloc_color('#CFFCFFCFF'))

                x_incr = int(self.__w / 20)

                x = self.__w_half
                while True:
                        self.__pixmap.draw_line(gc, x, 0, x, self.__h)
                        x -= x_incr
                        if x < 0:
                                break

                x = self.__w_half
                while True:
                        self.__pixmap.draw_line(gc, x, 0, x, self.__h)
                        x += x_incr
                        if x > self.__w:
                                break

                y_incr = int(self.__h / 20)

                y = self.__h_half
                while True:
                        self.__pixmap.draw_line(gc, 0, y, self.__w, y)
                        y -= y_incr
                        if y < 0:
                                break

                y = self.__h_half
                while True:
                        self.__pixmap.draw_line(gc, 0, y, self.__w, y)
                        y += y_incr
                        if y > self.__h:
                                break

                # draw cross-hairs...

                gc = widget.get_style().black_gc

                self.__pixmap.draw_line(gc, self.__w_half, 0, self.__w_half, self.__h)
                self.__pixmap.draw_line(gc, 0, self.__h_half, self.__w, self.__h_half)

                # draw radar field-of-view...

                def intersects(theta):

                        gc = widget.get_style().black_gc

                        gc.set_line_attributes(3, gtk.gdk.LINE_DOUBLE_DASH,
                                               gtk.gdk.CAP_NOT_LAST, gtk.gdk.JOIN_MITER)

                        if theta == 0:
                                x_intersect = self.__w
                                y_intersect = self.__h_half
                        elif theta > 0 and theta < 90:
                                phe = math.radians(90 - theta)
                                x_intersect = self.__w_half + int(self.__h_half * math.tan(phe))
                                y_intersect = 0
                        elif theta >= 90 and theta < 180:
                                phe = math.radians(90 - (180 - theta))
                                x_intersect = self.__w_half - int(self.__h_half * math.tan(phe))
                                y_intersect = 0
                        elif theta == 180:
                                x_intersect = 0
                                y_intersect = self.__h_half
                        elif theta > 180 and theta < 270:
                                phe = math.radians(270 - theta)
                                x_intersect = self.__w_half - int(self.__h_half * math.tan(phe))
                                y_intersect = self.__h
                        elif theta >= 270 and theta < 360:
                                phe = math.radians(90 - (360 - theta))
                                x_intersect = self.__w_half + int(self.__h_half * math.tan(phe))
                                y_intersect = self.__h
                        elif theta == 360:
                                x_intersect = self.__w
                                y_intersect = self.__h_half
                        else:
                                return

                        self.__pixmap.draw_line(gc,
                                                self.__w_half, self.__h_half,
                                                x_intersect, y_intersect)

                        gc.set_line_attributes(1, gtk.gdk.LINE_SOLID,
                                               gtk.gdk.CAP_NOT_LAST, gtk.gdk.JOIN_MITER)

                look_left = self.boresight + 45
                if look_left > 360:
                        look_left = look_left - 360
                intersects(look_left)

                look_right = look_left - 90
                if look_right < 0:
                        look_right = 360 + look_right
                intersects(look_right)

        def on_drawingarea_expose_event(self, widget, event):
                x, y, width, height = event.area
                gc = widget.get_style().fg_gc[gtk.STATE_NORMAL]
                widget.window.draw_drawable(gc, self.__pixmap, x, y, x, y, width, height)

        def on_drawingarea_realize(self, widget):
                pass

        def __init__(self, *args, **kwargs):
                Widget.__init__(self, *args, **kwargs)

                path = os.environ['ELROND_ETC']
                name = 'elrond-plane'

                self.loadui(path, name)
                self.loaddb(path, name)

                self.__drawingarea = self.builder.get_object('drawingarea')
                self.__layout = self.__drawingarea.create_pango_layout('')

                self.boresight = 0

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
