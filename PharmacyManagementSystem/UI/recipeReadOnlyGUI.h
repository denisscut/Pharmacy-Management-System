#pragma once
#include <QtWidgets/QApplication>
#include <qlabel.h>
#include <qpainter.h>
#include <QPaintEvent>
class RecipeReadOnlyGUI : public QWidget, public Observer {
	Recipe& recipe;
public:
	RecipeReadOnlyGUI(Recipe& recipe) : recipe{ recipe } {
		setMouseTracking(true);
		recipe.addObserver(this);
		
	}

	void update() override{
		repaint();
	}
protected:
	void paintEvent(QPaintEvent*) override {
		QPainter p{ this };
		int nr = (int)recipe.getRecipe().size(), thickness, margin = 5, x = margin;
		double mn = 1;

		if (nr > 0) {
			thickness = (width() - 2 * margin) / nr;
			int space = (int)sqrt(thickness);
			thickness -= space;
			for (auto med : recipe.getRecipe()) {
				if (med.getPret() > mn)
					mn = med.getPret();
			}
			double e = height() / mn;
			//p.setPen(QPen(Qt::black, thickness));
			for (auto med : recipe.getRecipe()) {
				QRect* rect = new QRect(x, 0, thickness, (int)med.getPret() * e - 2);
				p.drawRect(*rect);
				//p.drawLine(x + thickness / 2, 0, x + thickness / 2, med.getPret() * e);
				x += (thickness + space);
			}
		}
	}
};
//640 - 480