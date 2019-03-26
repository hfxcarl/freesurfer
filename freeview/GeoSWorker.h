#ifndef GEOSWORKER_H
#define GEOSWORKER_H

#include <QObject>
#include <QThread>

class LayerMRI;
class GeodesicMatting;

class GeoSWorker : public QObject
{
  Q_OBJECT
public:
  explicit GeoSWorker(QObject *parent = nullptr);
  ~GeoSWorker();

signals:
  void ComputeTriggered();
  void ApplyTriggered();
  void ApplyFinished();
  void ComputeFinished(bool bSuccess);

public slots:
  void Compute(LayerMRI* mri, LayerMRI* seg, LayerMRI* seeds, int max_distance = -1);
  void Apply(LayerMRI* seg, LayerMRI* filled);
  void Abort();

private slots:
  void DoCompute();
  void DoApply();

private:
  LayerMRI* m_seeds;
  LayerMRI* m_mri;
  LayerMRI* m_seg;
  LayerMRI* m_filled;
  int     m_nMaxDistance;
  GeodesicMatting*  m_geos;

  QThread   m_thread;
};

#endif // GEOSWORKER_H
