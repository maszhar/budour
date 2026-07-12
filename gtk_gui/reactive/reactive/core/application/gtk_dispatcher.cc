/*
 * Copyright (C) 2026 Fikri Mustofa <fikrimustofa024@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "gtk_dispatcher.h"
#include <glib.h>

namespace MYAPP
{
  namespace
  {
    gboolean dispatch_callback(gpointer data)
    {
      std::unique_ptr<std::function<void()>> callback(
          static_cast<std::function<void()> *>(data));

      (*callback)();

      return FALSE;
    }
  }

  GtkDispatcher &GtkDispatcher::instance()
  {
    static GtkDispatcher dispatcher;
    return dispatcher;
  }

  void GtkDispatcher::initialize()
  {
    _gtk_thread_id = std::this_thread::get_id();
  }

  void GtkDispatcher::dispatch(std::function<void()> callback)
  {
    if (std::this_thread::get_id() == _gtk_thread_id)
    {
      callback();
      return;
    }

    g_idle_add(
        dispatch_callback,
        new std::function<void()>(std::move(callback)));
  }
}