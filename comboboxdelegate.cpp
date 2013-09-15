#include "comboboxdelegate.h"

comboBoxDelegate::comboBoxDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *comboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   QComboBox *editor = new QComboBox(parent);
   editor->addItem("Not Completed");
   editor->addItem("Casual");
   editor->addItem("Normal");
   editor->addItem("Hard");
   editor->addItem("Epic");
   return editor;
}

void comboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    comboBox->setCurrentIndex(comboBox->findText(index.data().toString()));
}

void comboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString value = comboBox->currentText();

    model->setData(index, value , Qt::EditRole);
}

void comboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
     editor->setGeometry(option.rect);
}
