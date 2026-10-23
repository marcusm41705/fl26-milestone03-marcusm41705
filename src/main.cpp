#include "aiws/gui/main_window.hpp"

#include <QApplication>
#include <QMessageBox>
#include <QWidget>
//Define the ExitCallback function used to confirm an Exit request.
void confirm_exit(QWidget* parent){
    QMessageBox::StandardButton choice_msg = QMessageBox::question(parent, "Exit AI Workspace", "Are you sure you want to exit works?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(choice_msg  == QMessageBox::Yes){
        QCoreApplication::quit();
    }
}
int main(int argc, char* argv[]) {
    //Creating QT app
    QApplication app(argc, argv);
    aiws::gui::MainWindow m_window;
    //register exit callback
    m_window.set_exit_callback(&confirm_exit);
    //Displaying app window
    m_window.show();
    return app.exec();
    
}
