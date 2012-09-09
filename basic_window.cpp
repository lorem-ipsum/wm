#include "basic_window.h"
#include "ptr.h"
#include "xwindow.h"

void
BasicWindow::remove_focus()
{
  if (focus != nullptr)
    focus->remove_focus();

  focus = nullptr;
}

void
BasicWindow::reset_focus(BasicWindow* win)
{
  // if we are part of the old chain and the new focus isn't the
  // old one we are the crossing. Tell the old part about the loss
  if (focus != nullptr && focus != win)
    focus->remove_focus();

  // set focus and move up the chain till top
  focus = win;
  if (parent != nullptr)
    parent->reset_focus(this);
}

XWindow*
WindowStorage::new_xwindow(xcb_window_t id)
{
  XWindow win(id);
  auto unique_win = make_unique<XWindow>(win);
  insert(make_pair(id, std::move(unique_win)));
  return unique_win.get();
}