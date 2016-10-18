#ifndef ANPROPERTY_H
#define ANPROPERTY_H

#include <QWidget>
#include "ui_AnimationForm.h"
#include "../GUI/Glyph/Animation.h"

using namespace std;

class AnimationForm : public QWidget
{
    Q_OBJECT

private:
    Ui::AnimationForm *ui;
    Animation _an;

public:
    explicit AnimationForm (QWidget *parent = 0);
    ~AnimationForm  ();
    void setProperty (const Animation &);
    Animation getProperty ();
    void debugPrint ();
};

#endif // AnProperty_H
