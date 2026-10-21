#include "aiws/gui/main_window.hpp"
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include<QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <exception>
namespace aiws::gui {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    // TODO: Construct the M3 application window, compose the GUI components,
    // establish layouts/presentation, connect events, and establish initial state.
    
    setWindowTitle("AI Workspace");
    resize(900,900); //Setting up application window
    //Setting up widget and main Layout
    QWidget* central = new QWidget(this);
    QVBoxLayout* main_lay = new QVBoxLayout(central);
    //Setting up application title and header
    QLabel* title_label = new QLabel("AI Workspace", central);
    title_label->setAlignment(Qt::AlignCenter);
   title_label->setStyleSheet("background-color: #00008B;" "color: white;" "font-size: 20px;" "font-weight: bold;"
    "padding: 12px;");
   main_lay->addWidget(title_label);
   //Workspace component
   workspace_widget_ = new WorkspaceWidget(central);
   main_lay->addWidget(workspace_widget_, 1);
   //Setting up bottom status and the action buttons
   QHBoxLayout* bottom_lay = new QHBoxLayout();
   status_label_ = new QLabel("Ready.", central);
   reset_button_ = new QPushButton("Reset", central);
   exit_button_ = new QPushButton("Exit", central);
   reset_button_->setStyleSheet("background-color: #d6ac50;" "color: white;" "padding: 8px;");
   exit_button_->setStyleSheet("background-color: #800020;" "color: white;" "padding: 8px;");
   bottom_lay->addWidget(status_label_);
   bottom_lay->addStretch();
   bottom_lay->addWidget(reset_button_);
   bottom_lay->addWidget(exit_button_);
   main_lay->addLayout(bottom_lay);
   //Installing the central widget
   setCentralWidget(central);
   //Connecting the WorkspaceWidget elements
   connect(workspace_widget_, &WorkspaceWidget::add_document_requested, this, &MainWindow::add_document);
   connect(workspace_widget_, &WorkspaceWidget::build_corpus_requested,this, &MainWindow::build_corpus);
   connect(workspace_widget_, &WorkspaceWidget::document_selected, this, &MainWindow::document_selected);
   //Connecting the reset and exit elements
   connect(reset_button_, &QPushButton::clicked, this, &MainWindow::reset_application);
   connect(exit_button_, &QPushButton::clicked, this, &MainWindow::exit_application);
   //Initializing the workspace states
   workspace_widget_->set_corpus_status("Corpus: Not built");
   workspace_widget_->set_build_corpus_enabled(false);
}

void MainWindow::set_exit_callback(ExitCallback callback) noexcept {
    exit_callback_ = callback;
}

void MainWindow::add_document() {
    // TODO
    //Opening a file dialog used to select a text file
    QString file_path = QFileDialog::getOpenFileName(this, "Add Document", QString(), "Text Files (*.txt);;All Files (*)");
    if(file_path.isEmpty()){
        return;
    }
    //Retrieve the absolute file path and filename
    QFileInfo file_info(file_path);
    QString document_id = file_info.absoluteFilePath();
    QString document_title = file_info.fileName();
    //Opens the file selected
    QFile file(document_id);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this, "File Error", "Unable to open the selected document.");
        return;
    }
    //Reads entire file
    QByteArray file_data = file.readAll();
    if(file.error() != QFileDevice::NoError){
        QMessageBox::warning(this, "File Error", "Unable to read the selected document.");
        return;
    }
    file.close();
    //Constructign the document using the class from Milestone 2
    Document document(document_id.toUtf8().toStdString(), document_title.toUtf8.toStdString(), file_data.toStdString());
    try { //Add document to backend workspace
        workspace_.add_document(document);
    } catch (const std::exception& error){
        QMessageBox::warning(this, "Document Error", QString::fromUtf8(error.what()));
        return;
    }
    //Add title to Gui
    workspace_widget_->add_document(document_title);
    //Workspace changed
    invalidate_corpus();
    status_label_->setText(QString("Document added: %1").arg(document_title));

}

void MainWindow::build_corpus() {
    //if to stop building an empty workspace
    if(workspace_.documents().empty()){
        return;
    }
    //Rebuilding using the backend from Milestone 2
    processing_core_.rebuild(workspace_);
    corpus_current_ = true; //marking the corpus as current
    clear_processing_outputs(); //Clearing the previous processing output
    //Display number of chunks
    QString chunk_status = QString("Corpus: %1 chunks").arg(static_cast<qulonglong>(processing_core_.chunk_count()));
    workspace_widget_->set_corpus_status(chunk_status);
    status_label_->setText("Corpus built successfully.");
}

void MainWindow::document_selected(int row) {
    //Grab documents stored in Workspace
    const auto& docs = workspace_.documents();
}

void MainWindow::search_requested(const QString& query, int k) {
    // TODO
    (void)query;  // To suppress unused-parameter warning.
    (void)k;  // To suppress unused-parameter warning.
}

void MainWindow::query_changed(const QString& query) {
    // TODO
    (void)query;  // To suppress unused-parameter warning.
}

void MainWindow::build_context_requested(int token_budget) {
    // TODO
    (void)token_budget;  // To suppress unused-parameter warning.
}

void MainWindow::source_document_requested(const QString& document_id) {
    // TODO
    (void)document_id;  // To suppress unused-parameter warning.
}

void MainWindow::term_inspection_requested(const QString& term,
                                           const QString& chunk_id) {
    // TODO
    (void)term;  // To suppress unused-parameter warning.
    (void)chunk_id;  // To suppress unused-parameter warning.
}

void MainWindow::reset_application() {
    // TODO
}

void MainWindow::exit_application() {
    if(exit_callback_ != nullptr){
        exit_callback_(this);
    }
}

void MainWindow::update_action_states() {
    // TODO
}

void MainWindow::invalidate_corpus() {
    // TODO
}

void MainWindow::clear_processing_outputs() {
    // TODO
}

}  // namespace aiws::gui
