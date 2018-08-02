#ifndef POINCARE_INTEGRAL_LAYOUT_NODE_H
#define POINCARE_INTEGRAL_LAYOUT_NODE_H

#include <poincare/layout_cursor.h>
#include <poincare/layout_node.h>
#include <poincare/layout_reference.h>
#include <kandinsky/text.h>

namespace Poincare {

class IntegralLayoutNode : public LayoutNode {
public:
  constexpr static KDCoordinate k_symbolHeight = 4;
  constexpr static KDCoordinate k_symbolWidth = 4;

  using LayoutNode::LayoutNode;

  // LayoutNode
  void moveCursorLeft(LayoutCursor * cursor, bool * shouldRecomputeLayout) override;
  void moveCursorRight(LayoutCursor * cursor, bool * shouldRecomputeLayout) override;
  void moveCursorUp(LayoutCursor * cursor, bool * shouldRecomputeLayout, bool equivalentPositionVisited = false) override;
  void moveCursorDown(LayoutCursor * cursor, bool * shouldRecomputeLayout, bool equivalentPositionVisited = false) override;
  void deleteBeforeCursor(LayoutCursor * cursor) override;
  int writeTextInBuffer(char * buffer, int bufferSize, Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const override;
  LayoutNode * layoutToPointWhenInserting() override {
    assert(lowerBoundLayout() != nullptr);
    return lowerBoundLayout();
  }
  char XNTChar() const override { return 'x'; }

  // TreeNode
  // size() does not need to be overrided
  int numberOfChildren() const override { return 3; }
#if TREE_LOG
  const char * description() const override { return "IntegralLayout"; }
#endif

protected:
  // LayoutNode
  void computeSize() override;
  void computeBaseline() override;
  KDPoint positionOfChild(LayoutNode * child) override;
private:
  constexpr static KDText::FontSize k_fontSize = KDText::FontSize::Large;
  constexpr static KDCoordinate k_boundHeightMargin = 8;
  constexpr static KDCoordinate k_boundWidthMargin = 5;
  constexpr static KDCoordinate k_integrandWidthMargin = 2;
  constexpr static KDCoordinate k_integrandHeigthMargin = 2;
  constexpr static KDCoordinate k_lineThickness = 1;
  LayoutNode * integrandLayout() { return childAtIndex(0); }
  LayoutNode * lowerBoundLayout() { return childAtIndex(1); }
  LayoutNode * upperBoundLayout() { return childAtIndex(2); }
  void render(KDContext * ctx, KDPoint p, KDColor expressionColor, KDColor backgroundColor) override;
};

class IntegralLayoutRef : public LayoutReference {
public:
  IntegralLayoutRef(LayoutRef integrand, LayoutRef lowerBound, LayoutRef upperBound) :
    IntegralLayoutRef()
  {
    addChildTreeAtIndex(integrand, 0, 0);
    addChildTreeAtIndex(lowerBound, 1, 1);
    addChildTreeAtIndex(upperBound, 2, 2);
  }
  IntegralLayoutRef(TreeNode * n) : LayoutReference(n) {}
private:
  IntegralLayoutRef() :
    LayoutReference()
  {
    TreeNode * node = TreePool::sharedPool()->createTreeNode<IntegralLayoutNode>();
    m_identifier = node->identifier();
  }
};

}

#endif