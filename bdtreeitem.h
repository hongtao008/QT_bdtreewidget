#ifndef BD_TREEITEM_H
#define BD_TREEITEM_H

#include <QFrame>
#include <functional>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>

namespace bd
{
    // �ڵ�����
    enum NodeType {
        None,
        Top,
        Parent,
        Child
    };

    struct ItemInfo {
        // �ؼ�չʾ����
        QVariant showData;

        // �������
        std::string parentId;           // ���ڵ�ID
        std::string id;                 // ��ǰ�ڵ�ID
        NodeType type;              // �ڵ�����
        bool isExpand;              // �Ƿ�չ����Child�ڵ���Ч��
        int height;                 // �ڵ�widget�߶�
        QList<ItemInfo> childList;  // �ӽڵ��б�Child�ڵ���Ч��

        ItemInfo() { }
        ItemInfo(const std::string& _parentId, const std::string& _id, NodeType type_, const QVariant &_showData, int _height)
            : parentId(_parentId), id(_id), type(type_), showData(_showData), height(_height) {
            isExpand = (type_ == Child);
        }
    };

    class ItemWidget : public QFrame
    {
        Q_OBJECT
    public:
        ItemWidget(QWidget *parent = 0);
        void setData(const ItemInfo &info);
        const ItemInfo& data();
        ItemInfo& mutableData();
        void setSelected(bool isSelected);
        bool isSelected() const;

    signals:
        void sigSelected(bool isSelected);
        void sigMousePress(QMouseEvent *event);
        void sigMouseRelease(QMouseEvent *event);
        void sigMouseDoubleClick(const QString &from = "");
        void sigError(const std::string& id, int errcode = 0);
        void sigMouseEnter();
        void sigMouseLeave();

    protected:
        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void mouseDoubleClickEvent(QMouseEvent *event);
        void enterEvent(QEvent *);
        void leaveEvent(QEvent *);

    private:
        virtual void updateData(const ItemInfo &info);

    protected:
        ItemInfo m_info;
        bool m_isSelected;
    };

    class ParentWidget : public ItemWidget
    {
        Q_OBJECT
    public:
        ParentWidget(QWidget *parent = 0);

    private:
        virtual void updateData(const ItemInfo &info);

    private:
        QLabel *m_label;
    };

    class ChildWidget : public ItemWidget
    {
        Q_OBJECT
    public:
        ChildWidget(QWidget *parent = 0);

    protected:
        bool eventFilter(QObject *, QEvent *);

    private:
        virtual void updateData(const ItemInfo &info);
        void updateStyle();

    private:
        QLabel *m_image;
        QLabel *m_head;
        QLabel *m_content;
    };
}
#endif // TREEITEM_H
