/* -*- c++ -*- ----------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   https://www.lammps.org/, Sandia National Laboratories
   LAMMPS development team: developers@lammps.org

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QCompleter>
#include <QFont>
#include <QMap>
#include <QPlainTextEdit>
#include <QShortcut>
#include <QString>
#include <QStringList>

class CodeEditor : public QPlainTextEdit {
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    void setFont(const QFont &newfont);
    void setCursor(int block);
    void setHighlight(int block, bool error);
    void setReformatOnReturn(bool flag) { reformat_on_return = flag; }
    void setAutoComplete(bool flag) { automatic_completion = flag; }
    QString reformatLine(const QString &line);
    void setCommandList(const QStringList &words);

    static constexpr int NO_HIGHLIGHT = 1 << 30;

protected:
    void resizeEvent(QResizeEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    bool canInsertFromMimeData(const QMimeData *source) const override;
    void dropEvent(QDropEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &rect, int dy);
    void get_help();
    void find_help(QString &page, QString &help);
    void open_help();
    void reformatCurrentLine();
    void runCompletion();
    void insertCompletedCommand(const QString &completion);

private:
    QWidget *lineNumberArea;
    QShortcut *help_action;
    QCompleter *command_completer;
    int highlight;
    bool reformat_on_return;
    bool automatic_completion;

    QMap<QString, QString> cmd_map;
    QMap<QString, QString> fix_map;
    QMap<QString, QString> compute_map;
    QMap<QString, QString> pair_map;
    QMap<QString, QString> bond_map;
    QMap<QString, QString> angle_map;
    QMap<QString, QString> dihedral_map;
    QMap<QString, QString> improper_map;
    QMap<QString, QString> dump_map;
};

#endif
// Local Variables:
// c-basic-offset: 4
// End:
