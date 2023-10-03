#ifndef COMPUTATIONWORKER_H
#define COMPUTATIONWORKER_H

#include <QObject>
#include <QThread>

class ComputationWorker : public QObject {
    Q_OBJECT

public:
    explicit ComputationWorker(QObject *parent = nullptr);
    ~ComputationWorker();

public slots:
    void process();

signals:
    void imageReady(uint8_t **state);
    void finished();

private:
    // Put all necessary computation methods and variables here
};

#endif // COMPUTATIONWORKER_H
