#include <escher/solid_color_view.h>

SolidColorView::SolidColorView(KDColor color) :
  ChildlessView(),
  m_color(color)
{
}

void SolidColorView::drawRect(KDRect rect) {
  KDFillRect(rect, m_color);
}
