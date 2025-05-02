#ifndef MAIN_WGT_H
#define MAIN_WGT_H

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

#include "mylineedit.hpp"

class Main_Wgt : public QWidget
{
	Q_OBJECT
private:
	uint8_t mask = 0;
	QTimer *timerFindFileP = new QTimer(this);

protected:
	// layout 1:
	QLabel* lblMaskP;
	QComboBox* cmbboxFileMaskP;
	QLabel* lblDeleteFileP;
	QCheckBox* cbxDeleteFileP;
	// layout 2:
	QLabel* lblMaskTitleP;
	QLineEdit* ledMaskValueP;
	QPushButton* btnConfirmMaskP;
	// layout 3:
	QLabel* lblChooseFileP;
	MyLineEdit* myLineEditP;
	QPushButton* btnModifyFileP;

public:
	Main_Wgt(QWidget* parent = nullptr);
	~Main_Wgt();

	QLabel* createQLabel(const char *str = "");
	QComboBox* createQComboBox();
	QPushButton* createPushButton(const char* str = "");
	QLineEdit* createQLineEdit();

public slots:
	void slotSetFilePath(QString path);
	void slotCheckRange(QString id);
	void slotWriteMask();
	void slotModifyFile();
};
#endif // MAIN_WGT_H