#include "ui.h"

bool UI::isBoxFilled(QLineEdit * const input)
{
    return !input->text().isEmpty();
}

bool UI::isFileSelected(QLabel * const input)
{
    return !(input->text().isEmpty() || input->text() == QString("None"));
}

void UI::disableButton(QPushButton *input)
{
    input->setEnabled(false);
}

void UI::enableButton(QPushButton *input)
{
    input->setEnabled(true);
}

int UI::comboBoxIndex(QComboBox* box, QString str)
{
    // if not found, just default to 0
    int index = box->findText(str);
    return (index < 0) ? 0 : index;
}
