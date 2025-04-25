#ifndef MY_LINE_EDIT_H
#define MY_LINE_EDIT_H

#include <QFileDialog>
#include <QLineEdit>

class MyLineEdit : public QLineEdit
{
	Q_OBJECT
private:
	size_t fileMode = 0;
public:
	MyLineEdit(const QString &contents = "", QWidget *parent = nullptr) : QLineEdit(contents, parent) {}

	virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

public slots:
	void slotFileMode(int mode);
signals:
	void signPath(QString path);
};

#endif // MY_LINE_EDIT_H