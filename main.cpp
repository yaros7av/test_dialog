/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2018 Yaroslav Kornachevskyi
//
// This code is an example of proxy model usage
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <QApplication>
#include <QSortFilterProxyModel>
#include <QFileSystemModel>
#include <QFileDialog>
#include <QDebug>

class FileFilterProxyModel : public QSortFilterProxyModel
{
	bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
	{
		QFileSystemModel* fileModel = qobject_cast<QFileSystemModel*>(sourceModel());
		QFileInfo file( fileModel->filePath(sourceModel()->index(sourceRow, 0, sourceParent)) );
		
		if (fileModel!=NULL && file.isExecutable())
			return true;
		else
			return false;
	}
};

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName( "test_dialog" );

    QFileDialog dialog;
    FileFilterProxyModel* proxyModel = new FileFilterProxyModel;
    dialog.setProxyModel(proxyModel);
    dialog.setOption(QFileDialog::DontUseNativeDialog);

    if( dialog.exec() == QDialog::Accepted )
        qDebug() << dialog.selectedFiles();
   
    return 0;
}
