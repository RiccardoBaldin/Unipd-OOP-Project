#ifndef TREE_HPP
#define TREE_HPP

#include <QTreeWidget>

class Biblioteca;

class Tree : public QTreeWidget {
    Q_OBJECT

public:
    explicit Tree(Biblioteca *biblioteca, QWidget *parent = nullptr);
        void updateTree();

private:
    Biblioteca *biblioteca;
    QTreeWidgetItem *libreria;
    QTreeWidgetItem *libri;
    QTreeWidgetItem *film;
    QTreeWidgetItem *serie;
    
    void populateTree();

signals:
    void updateTreeSignal();
};

#endif // TREE_HPP