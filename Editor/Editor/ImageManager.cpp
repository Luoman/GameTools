#include <QDir>
#include <QString>
#include <QStringList>
#include <QRegExp>
#include <QPixmap>
#include <iostream>

#include "ImageManager.h"

ImageManager::ImageManager()
{
    m_pDefaultImg = new t_Image;
    m_pDefaultImg->m_sName = "zelda4.png";
    m_pDefaultImg->m_iImage = QPixmap("./Pictures/zelda4.png");
}

ImageManager::~ImageManager()
{
    std::map<int,t_Image *>::iterator it;

    for (it = m_mImages.begin(); it != m_mImages.end(); ++it)
        delete it->second;
    m_mImages.clear();
    m_mMonsters.clear();
    delete m_pDefaultImg;
}

void                ImageManager::openImage(const QString &)
{

}

void                ImageManager::createListImage()
{
    QDir            dir(m_sPath.c_str());
    QStringList     l(dir.entryList());
    QRegExp         rx("*.png");
    t_Image         *img;
    QStringList::const_iterator constIterator;
    int             i = 0;

    rx.setPatternSyntax(QRegExp::Wildcard);
    l = l.filter(rx);
    for (i = 0, constIterator = l.constBegin(); constIterator != l.constEnd(); ++constIterator, ++i)
    {
        img = new t_Image;
        img->m_iImage = QPixmap(QString(m_sPath.c_str()) + "\\" + (*constIterator).toLocal8Bit().constData());
        img->m_sName = (*constIterator).toLocal8Bit().constData();
        m_mImages[i] = img;
//        for (int x = 4; x < 4 * 60 ; x = x + 4)
//            m_mImages[i + x] = img;
    }
    m_mMonsters["wisp"] = QPixmap(QString("./Pictures/Monsters/wisp.png"));
    m_mMonsters["antifairy"] = QPixmap(QString("./Pictures/Monsters/antifairy.png"));
    m_mMonsters["bat"] = QPixmap(QString("./Pictures/Monsters/bat.png"));
    m_mMonsters["leever"] = QPixmap(QString("./Pictures/Monsters/leever.png"));
    m_mMonsters["beetle"] = QPixmap(QString("./Pictures/Monsters/beetle.png"));
}

t_Image             *ImageManager::getDefaultImage() const
{
    return (m_pDefaultImg);
}

const std::map<int, t_Image *>  &ImageManager::getImages() const
{
    return (m_mImages);
}

t_Image             *ImageManager::getImageFromID(int id)
{
    return (m_mImages[id]);
}

void                ImageManager::setPath(const std::string &path)
{
    m_sPath = path;
}

QPixmap             &ImageManager::getMonsterImage(const std::string &monster)
{
    return (m_mMonsters[monster]);
}

t_Image             *ImageManager::getImageByName(QString &name)
{
    std::map<int, t_Image *>::iterator      it;

    for (it = m_mImages.begin(); it != m_mImages.end(); ++it)
        if (it->second->m_sName == name)
            return (it->second);
    return (m_pDefaultImg);
}
