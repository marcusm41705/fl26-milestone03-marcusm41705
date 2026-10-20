#include "aiws/gui/workspace_widget.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPlainTextEdit>
#include <QPushButton>
namespace aiws::gui {

WorkspaceWidget::WorkspaceWidget(QWidget* parent) : QWidget(parent) {
    // TODO: Construct and lay out the Workspace and Selected Document areas,
    // connect local widget events, and establish initial presentation state.
    auto* main_lay = new QHBoxLayout(this); //The main horizontal layout
    //Workspace on left side
    auto* left = new QWidget(this);
    auto left_lay = new QVBoxLayout(left);
    auto* wp_label = new QLabel("Workspace", left);
    //Initialize document and build corpus buttons
    add_document_button_ = new QPushButton("Add Document", left);
    build_corpus_button_ = new QPushButton("Build Corpus", left);
    document_list_ = new QListWidget(left);
    corpus_status_label_ = new QLabel("Corpus: Not built", left);
    //New layout for buttons
    auto* button_layout = new QHBoxLayout();
    button_layout->addWidget(add_document_button_);
    button_layout->addWidget(build_corpus_button_);

    left_lay->addWidget(wp_label);
    left_lay->addLayout(button_layout);
    left_lay->addWidget(document_list_);
    left_lay->addWidget(corpus_status_label_);

    //Layout from right side: selected document
    auto* right = new QWidget(this);
    auto right_lay = new QVBoxLayout(right)
    

}

void WorkspaceWidget::add_document(const QString& title) {
    // TODO
    (void)title;  // To suppress unused-parameter warning.
}

void WorkspaceWidget::select_document(int row) {
    // TODO
    (void)row;  // To suppress unused-parameter warning.
}

void WorkspaceWidget::show_selected_document(const QString& title,
                                              const QString& text) {
    // TODO
    (void)title;  // To suppress unused-parameter warning.
    (void)text;  // To suppress unused-parameter warning.
}

void WorkspaceWidget::clear_selected_document() {
    // TODO
}

void WorkspaceWidget::set_corpus_status(const QString& text) {
    // TODO
    (void)text;  // To suppress unused-parameter warning.
}

void WorkspaceWidget::set_build_corpus_enabled(bool enabled) {
    // TODO
    (void)enabled;  // To suppress unused-parameter warning.
}

void WorkspaceWidget::reset() {
    // TODO
}

}  // namespace aiws::gui
