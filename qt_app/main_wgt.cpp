#include "main_wgt.hpp"

#include <QVBoxLayout>
// #include <stdio.h>
// #include <stdint.h>

Main_Wgt::Main_Wgt(QWidget* parent) : QWidget(parent)
{
	setWindowTitle("Hummingbird");
	this->setMinimumSize(350, 300);
	
	// create Main layout:
	auto* vblayMainP = new QVBoxLayout(this);
	
	{// layout 1:
		auto* hblayP = new QHBoxLayout(this);
		lblMaskP = createQLabel("File Mask");
		cmbboxFileMaskP = createQComboBox();

		hblayP->addWidget(lblMaskP);
		hblayP->addWidget(cmbboxFileMaskP);
		vblayMainP->addLayout(hblayP);
	}
	{// layout 2:
		auto* hblayP = new QHBoxLayout(this);
		lblMaskTitleP = createQLabel("Input Mask");;
		ledMaskValueP = createQLineEdit();
		btnConfirmMaskP = createPushButton("Confirm");

		hblayP->addWidget(lblMaskTitleP);
		hblayP->addWidget(ledMaskValueP);
		hblayP->addWidget(btnConfirmMaskP);
		vblayMainP->addLayout(hblayP);
	}
	{// layout 3:
		auto* hblayP = new QHBoxLayout(this);
		lblChooseFileP = createQLabel("File");
		myLineEditP = new MyLineEdit;
		btnReadFileP = createPushButton("Modify");

		hblayP->addWidget(lblChooseFileP);
		hblayP->addWidget(myLineEditP);
		hblayP->addWidget(btnReadFileP);
		vblayMainP->addLayout(hblayP);
	}
	vblayMainP->addStretch();

	connect(cmbboxFileMaskP, &QComboBox::activated, myLineEditP, &MyLineEdit::slotFileMode);
	connect(myLineEditP, &MyLineEdit::signPath, this, &Main_Wgt::slotSetFilePath);
	connect(btnConfirmMaskP, &QPushButton::clicked, this, &Main_Wgt::slotWriteMask);
	connect(btnReadFileP, &QPushButton::clicked, this, &Main_Wgt::slotBtnWorks);
}

Main_Wgt::~Main_Wgt()
{
}

QLabel* Main_Wgt::createQLabel(const char *str)
{
	QLabel* labelP = new QLabel(str);
	labelP->setAlignment(Qt::AlignCenter);
	labelP->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
	return labelP;
}

QComboBox* Main_Wgt::createQComboBox()
{
	QComboBox* tmpP = new QComboBox;
	tmpP->addItem(".txt");
	tmpP->addItem(".bin");
	return tmpP;
}

QPushButton* Main_Wgt::createPushButton(const char* str)
{
	QPushButton* btnTmpP = new QPushButton(str);
	btnTmpP->setStyleSheet("background-color: Gainsboro");
	return btnTmpP;
}

QLineEdit* Main_Wgt::createQLineEdit()
{
	QLineEdit* tmpLEd = new QLineEdit();
	QIntValidator* valid = new QIntValidator(0, UINT64_MAX);
	tmpLEd->setValidator(valid);
	return tmpLEd;
}

void Main_Wgt::slotSetFilePath(QString path)
{
	if(!path.isEmpty())
	{
		myLineEditP->setText(path);
	}
}

void Main_Wgt::slotWriteMask()
{
	
}

void Main_Wgt::slotBtnWorks()
{
}