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
		lblDeleteFileP = createQLabel("Delete file");
		cbxDeleteFileP = new QCheckBox();
		cbxDeleteFileP->setChecked(false);

		hblayP->addWidget(lblMaskP);
		hblayP->addWidget(cmbboxFileMaskP);
		hblayP->addWidget(lblDeleteFileP);
		hblayP->addWidget(cbxDeleteFileP);
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
		btnModifyFileP = createPushButton("Modify");

		hblayP->addWidget(lblChooseFileP);
		hblayP->addWidget(myLineEditP);
		hblayP->addWidget(btnModifyFileP);
		vblayMainP->addLayout(hblayP);
	}
	vblayMainP->addStretch();

	connect(cmbboxFileMaskP, &QComboBox::activated, myLineEditP, &MyLineEdit::slotFileMode);
	connect(myLineEditP, &MyLineEdit::signPath, this, &Main_Wgt::slotSetFilePath);
	connect(ledMaskValueP, &QLineEdit::textChanged, this, &Main_Wgt::slotCheckRange);
	connect(btnConfirmMaskP, &QPushButton::clicked, this, &Main_Wgt::slotWriteMask);
	connect(btnModifyFileP, &QPushButton::clicked, this, &Main_Wgt::slotModifyFile);
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
	QIntValidator* valid = new QIntValidator(0, 255);
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

void Main_Wgt::slotCheckRange(QString id)
{
	QVariant variant(id);
	int num = variant.toInt();
	if(num > 255)
	{
		num = 255;
		ledMaskValueP->setText(QString::number(num));
	}
}

void Main_Wgt::slotWriteMask()
{
	mask = ledMaskValueP->text().toUInt();
}

void Main_Wgt::slotModifyFile()
{
	QByteArray bAr;
	QFile file(myLineEditP->text());
	qDebug() << "FILE NAME is " << file.fileName();
	if(file.open(QIODevice::ReadWrite))
	{
		bAr = file.readAll();
		for(size_t i = 0; i < bAr.size(); i++)
		{
			bAr[i] = bAr[i] ^ mask;
		}

		if(cbxDeleteFileP->isChecked())
		{
			file.remove();
			QFile fileNew(QFileDialog::getSaveFileName(this, "Name file", "byteArray_list", "*.txt;; *.bin")); // save changed byteAr in file
			if(fileNew.open(QIODevice::ReadWrite))
			{
				fileNew.resize(0);
				fileNew.write(bAr);
			}
			fileNew.close();
		}
		else
		{
			file.resize(0);
			file.write(bAr);
			file.close();
		}
	}
}