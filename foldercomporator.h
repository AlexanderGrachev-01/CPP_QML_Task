#pragma once

#include <QDebug>
#include <QObject>
#include <QString>

class FolderComporator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString firstPath READ getFirstFolderP WRITE setFirstFolder)
    Q_PROPERTY(QString secondPath READ getSecondFolderP WRITE setSecondFolder)
    Q_PROPERTY(QString matchingResult READ getMatchingResult)

private:
    QString firstFolderPath;
    QString secondFolderPath;
    QString matchingResult;
    QVector <QString> matches;
    QVector <std::string> firstFolderFiles;
    QVector <std::string> secondFolderFiles;

public:
    FolderComporator();
    void setFirstFolder(QString firstFolderP);
    void setSecondFolder(QString secondFolderP);
    QString getFirstFolderP();
    QString getSecondFolderP();
    QString getMatchingResult();
    void clearMatches();
    void findFiles();
    Q_INVOKABLE void findEqualFiles();
};
