#pragma once

#include <memory>
#include <QDateTime>

class QString;

QDateTime getExifDateTime(const QString& path);
