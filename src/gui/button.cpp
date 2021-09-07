#include "button.h"
#include "common.h"
#include "dialog.h"
#include "dialogRunner.h"
#include "../jwin.h"
#include "../zquest.h"
#include <algorithm>
#include <utility>

#define FONT sized(nfont, lfont_l)

namespace gui
{

Button::Button(): text(), message(-1)
{
    setPreferredHeight(2.5_em);
}

void Button::setText(std::string newText)
{
    Size targetWidth=Size::em(newText.size());
    setPreferredWidth(std::max(targetWidth, 90_lpx));
    text=std::move(newText);
}

void Button::realize(DialogRunner& runner)
{
    alDialog=runner.push(shared_from_this(), DIALOG {
        jwin_button_proc,
        x, y, getWidth(), getHeight(),
        fgColor, bgColor,
        getAccelKey(text),
        D_NEW_GUI, // flags
        0, 0, // d1, d2
        (void*)text.c_str(), FONT, nullptr // dp, dp2, dp3
    });
}

int Button::onEvent(int event, MessageDispatcher sendMessage)
{
    assert(event==ngeCLICK);
    // jwin_button_proc doesn't seem to allow for a non-toggle button...
    alDialog->flags&=~D_SELECTED;
    if(message>=0)
        sendMessage(message, MessageArg::none);
    return -1;
}

}
