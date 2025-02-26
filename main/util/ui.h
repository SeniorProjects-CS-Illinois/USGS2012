#ifndef UI_H
#define UI_H

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>

namespace UI
{
    /**
     * Check if given input box has data.
     */
    bool isBoxFilled(QLineEdit* const input);

    /**
     * Check if given input box has numerical data.
     */
    bool isBoxNumerical(QLineEdit* const input);

    /**
     * Check if file has been selected. The check
     * is based on the label passed in, which is
     * the one that represents the file selected.
     * Therefore, this is true if and only if the
     * label text is nonempty and not 'None'.
     */
    bool isFileSelected(QLabel* const input);

    /**
     * Disable the input button.
     */
    void disableButton(QPushButton* input);

    /**
     * Enable the input button.
     */
    void enableButton(QPushButton* input);

    /**
     * Get the index of the given string in the stock combo box.
     * Returns 0 if stock not found, defaulting to 0th index stock.
     */
    int comboBoxIndex(QComboBox* box, QString str);
}

#endif // UI_H
