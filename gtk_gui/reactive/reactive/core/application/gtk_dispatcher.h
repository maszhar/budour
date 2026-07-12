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

#pragma once

#include <functional>
#include <thread>

namespace MYAPP
{
  class GtkDispatcher
  {
  public:
    static GtkDispatcher &instance();

    void initialize();

    void dispatch(std::function<void()> callback);

  private:
    GtkDispatcher() = default;

    GtkDispatcher(const GtkDispatcher &) = delete;
    GtkDispatcher &operator=(const GtkDispatcher &) = delete;

    GtkDispatcher(GtkDispatcher &&) = delete;
    GtkDispatcher &operator=(GtkDispatcher &&) = delete;

    std::thread::id _gtk_thread_id;
  };
}