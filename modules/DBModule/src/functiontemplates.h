#ifndef FUNCTIONTEMPLATES_H
#define FUNCTIONTEMPLATES_H

#include <QQmlListProperty>

class FunctionTemplates
{

public:
    FunctionTemplates();
protected:
    template <typename T>
    static void append(QQmlListProperty<T> *list, T* obj)
    {
        QVector<T*>* m_data = reinterpret_cast<QVector<T*>*>(list->data);
        if(obj) m_data->append(obj);
    }

    template <typename T>
    static qsizetype count(QQmlListProperty<T> *list)
    {
        QVector<T*>* m_data = reinterpret_cast<QVector<T*>*>(list->data);
        return m_data->size();
    }

    template <typename T>
    static T* at(QQmlListProperty<T> *list, qsizetype index)
    {
        QVector<T*>* m_data = reinterpret_cast<QVector<T*>*>(list->data);
        return (index >= 0 && index < m_data->size()) ? m_data->at(index) : nullptr;
    }

    template <typename T>
    static void clear(QQmlListProperty<T> *list)
    {
        QVector<T*>* m_data = reinterpret_cast<QVector<T*>*>(list->data);
        for(T* obj : *m_data)
        {
            delete obj;
        }
        m_data->clear();
    }

    template <typename T>
    static void replace(QQmlListProperty<T> *list, qsizetype index, T* obj)
    {
        QVector<T*>* m_data = reinterpret_cast<QVector<T*>*>(list->data);
        if(index >= 0 && index < m_data->size() && obj)
        {
            delete (*m_data)[index];
            (*m_data)[index] = obj;
        }
    }

    template <typename T>
    static void removeLast(QQmlListProperty<T> *list)
    {
        QVector<T*>* m_data = reinterpret_cast<QVector<T*>*>(list->data);
        if(!m_data->isEmpty())
        {
            delete m_data->last();
            m_data->removeLast();
        }
    }
};

#endif // FUNCTIONTEMPLATES_H
