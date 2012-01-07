/* Licensed under the MIT license: http://www.opensource.org/licenses/mit-license.php */

#include "MainWindow.h"

#include <iostream> 

#include "voronoi.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);

    //qout = new QDebugStream(std::cout, ui.txtCUDALog);

	// additional connections (because I can't figure out how to do this in Qt Designer :P)
	QObject::connect(ui.actionRun, SIGNAL(triggered()), this, SLOT(runCUDAProgram()));

}


void MainWindow::runCUDAProgram() {
    Voronoi* v = new Voronoi(); 
    v->main();
}

