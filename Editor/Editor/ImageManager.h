#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QImage>
#include <QString>
#include <QPixmap>

#include <map>

#include "Singleton.hh"

typedef struct  s_Image
{
    QPixmap     m_iImage;
    QString     m_sName;
}               t_Image;

class ImageManager : public Singleton<ImageManager>
{
public:
    friend class Singleton<ImageManager>;

private:
    ImageManager();
    ~ImageManager();

public:
    void openImage(const QString &file);
    void createListImage();

public:
    t_Image *getDefaultImage() const;
    const std::map<int, t_Image *> &getImages() const;
    t_Image *getImageFromID(int id);
    QPixmap     &getMonsterImage(const std::string &monster);
    t_Image *getImageByName(QString &name);

public:
    void setPath(const std::string &);

private:
    t_Image *m_pDefaultImg;
    std::map<int, t_Image *>  m_mImages;
    std::map<std::string, QPixmap> m_mMonsters;
    std::string m_sPath;
};

#endif // IMAGEMANAGER_H
