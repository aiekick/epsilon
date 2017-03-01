#ifndef ESCHER_BUTTON_H
#define ESCHER_BUTTON_H

#include <escher/view.h>
#include <escher/responder.h>
#include <escher/pointer_text_view.h>
#include <escher/invocation.h>

class Button : public View, public Responder {
public:
  Button(Responder * parentResponder, const char * textBody, Invocation invocation, KDText::FontSize size = KDText::FontSize::Small);
  bool handleEvent(Ion::Events::Event event) override;
  void setBackgroundColor(KDColor backgroundColor);
  KDSize minimalSizeForOptimalDisplay() override;
private:
  constexpr static KDCoordinate k_verticalMargin = 5;
  constexpr static KDCoordinate k_horizontalMargin = 10;
  int numberOfSubviews() const override;
  View * subviewAtIndex(int index) override;
  void layoutSubviews() override;
  PointerTextView m_pointerTextView;
  Invocation m_invocation;
  KDColor m_backgroundColor;
};

#endif
