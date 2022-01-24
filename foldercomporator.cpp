#include <iostream>
#include <functional>
#include <QDebug>
#include <fstream>
#include <string>
#include <filesystem>
#include <QFile>
#include <QDir>
#include "foldercomporator.h"

std::hash<std::string> str_hash;

// сеттеры и геттеры
FolderComporator::FolderComporator() {
}

void FolderComporator::setFirstFolder(QString firstFolderP) {
    std::string str = firstFolderP.toStdString().erase(0, 7);
    firstFolderPath = QString::fromStdString(str);
}
void FolderComporator::setSecondFolder(QString secondFolderP) {
    std::string str = secondFolderP.toStdString().erase(0, 7);
    secondFolderPath  = QString::fromStdString(str);
}

QString FolderComporator::getFirstFolderP() { return firstFolderPath; }
QString FolderComporator::getSecondFolderP() { return secondFolderPath; }
QString FolderComporator::getMatchingResult() { return matchingResult; }



// чистка вектора результатов
void FolderComporator::clearMatches() {
    matches.clear();
    firstFolderFiles.clear();
    secondFolderFiles.clear();
    matchingResult = "";
}



// функцияк записи адресов
void FolderComporator::findFiles() {
    qDebug() << "\n \n Поиск файлов...";
    QDir firstDir(firstFolderPath);
    QDir secondDir(secondFolderPath);
    QStringList firstFiles = firstDir.entryList(QStringList());
    QStringList secondFiles = secondDir.entryList(QStringList());
    foreach(QString filename, firstFiles) {
        firstFolderFiles.append(firstFolderPath.toStdString() + "/" + filename.toStdString());
        qDebug() << firstFolderPath + "/" + filename;
    }
    qDebug() << "Следующая папка";
    foreach(QString filename, secondFiles) {
        secondFolderFiles.append(secondFolderPath.toStdString() + "/" + filename.toStdString());
        qDebug() << secondFolderPath + "/" + filename;
    }
    qDebug() << "Поиск завершен \n \n \n";
}



// сравнение двух файлов
bool fileComparing(std::string firstPath, std::string secondPath) {
    QFile firstQFile(QString::fromStdString(firstPath));
    QFile secondQFile(QString::fromStdString(secondPath));
    if (!firstQFile.open(QIODevice::ReadOnly) || !secondQFile.open(QIODevice::ReadOnly)) {
        firstQFile.close();
        secondQFile.close();
        return false;
    }
    if (firstQFile.size() != secondQFile.size()) {
        firstQFile.close();
        secondQFile.close();
        return false;
    }

    std::ifstream firstFile(firstPath, std::ios_base::binary);
    std::ifstream secondFile(secondPath, std::ios_base::binary);

    if (!firstFile.is_open() || !secondFile.is_open()) {
        firstFile.close();
        secondFile.close();
        return false;
    }
    int step = 100;
    char firstBuff[step];
    char secondBuff[step];
    std::string firstData = firstBuff;
    std::string secondData = secondBuff;
    unsigned long point = 0;
    do {
        if (firstFile.eof()) {
            firstFile.close();
            secondFile.close();
            return true;
        }
        firstFile.seekg(point);
        secondFile.seekg(point);
        firstFile.read(firstBuff, step);
        secondFile.read(secondBuff, step);
        firstData = firstBuff;
        secondData = secondBuff;
        point += step;
    }
    while (str_hash(firstData) == str_hash(secondData));
    firstFile.close();
    secondFile.close();
    return false;
}



// функция поиска совпадений в двух папках
void FolderComporator::findEqualFiles() {
    clearMatches();
    findFiles();

    qDebug() << firstFolderFiles.count() << secondFolderFiles.count() << "Поиск совпадений...";
    // проходимся по файлам из двух папок и ищем совпадения
    for (int firstIndex = 0; firstIndex < firstFolderFiles.count(); ++firstIndex) {
        for (int secondIndex = 0; secondIndex < secondFolderFiles.count(); ++secondIndex) {
            if (!fileComparing(firstFolderFiles.at(firstIndex), secondFolderFiles.at(secondIndex))) {
            }
            else {
                qDebug() << QString::fromStdString(firstFolderFiles.at(firstIndex));
                qDebug() << QString::fromStdString(secondFolderFiles.at(secondIndex)) << "\n \n";
                matches.append(QString::fromStdString(firstFolderFiles.at(firstIndex)));
                matches.append(QString::fromStdString(secondFolderFiles.at(secondIndex)));
            }
        }
    }
    qDebug() << "Поиск завершен";

    // вывод
    for (int index = 0; index < matches.count(); ++index) {
        if (index % 2 == 0) {
            matchingResult += matches.at(index) + "\n";
        } else {
            matchingResult += matches.at(index) + "\n \n";
        }
    }
    if (matchingResult == "") {
        matchingResult = "No such files";
    }
    qDebug() << matchingResult;
}

