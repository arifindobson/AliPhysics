#include "AliAnalysisPIDParticle.h"
#include "TParticle.h"
#include "AliPID.h"
#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include "TMath.h"

ClassImp(AliAnalysisPIDParticle)

//___________________________________________________________

TLorentzVector AliAnalysisPIDParticle::fgLorentzVector;

//___________________________________________________________

Double_t
AliAnalysisPIDParticle::GetY() const
{
  
  fgLorentzVector.SetPtEtaPhiM(fPt, fEta, fPhi, GetMass());
  return fgLorentzVector.Rapidity();
}

//___________________________________________________________

Float_t
AliAnalysisPIDParticle::GetSign() const
{
  
  TDatabasePDG *dbpdg = TDatabasePDG::Instance();
  TParticlePDG *ppdg = dbpdg->GetParticle(fPdgCode);
  if (!ppdg)
    return 0.;
  return TMath::Sign(1., ppdg->Charge());
}

//___________________________________________________________

Int_t
AliAnalysisPIDParticle::GetPID() const
{
  /*
   * get PID
   */

  for (Int_t ipart = 0; ipart < AliPID::kSPECIES; ipart++)
    if (TMath::Abs(fPdgCode) == AliPID::ParticleCode(ipart))
      return ipart;
  return -1;

}

//___________________________________________________________

Double_t
AliAnalysisPIDParticle::GetMass() const
{
  /*
   * get mass
   */
  
  if (GetPID() == -1)
    return 0.;
  return AliPID::ParticleMass(GetPID());
}

//___________________________________________________________

AliAnalysisPIDParticle::AliAnalysisPIDParticle() :
  TObject(),
  fLabel(0),
  fPt(0.),
  fEta(0.),
  fPhi(0.),
  fPdgCode(0)
{
  /*
   * default constructor
   */
}

//___________________________________________________________

AliAnalysisPIDParticle::AliAnalysisPIDParticle(const AliAnalysisPIDParticle &source) :
  TObject(source),
  fLabel(source.fLabel),
  fPt(source.fPt),
  fEta(source.fEta),
  fPhi(source.fPhi),
  fPdgCode(source.fPdgCode)
{
  /*
   * copy constructor
   */
}

//___________________________________________________________

AliAnalysisPIDParticle &
AliAnalysisPIDParticle::operator=(const AliAnalysisPIDParticle &source)
{
  /*
   * operator=
   */

  if (&source == this) return *this;
  TObject::operator=(source);

  fLabel = source.fLabel;
  fPt = source.fPt;
  fEta = source.fEta;
  fPhi = source.fPhi;
  fPdgCode = source.fPdgCode;

  return *this;
}

//___________________________________________________________

AliAnalysisPIDParticle::~AliAnalysisPIDParticle()
{
  /*
   * default destructor
   */
}

//___________________________________________________________

void
AliAnalysisPIDParticle::Reset()
{
  /*
   * reset
   */

  fLabel = 0;
  fPt = 0.;
  fEta = 0.;
  fPhi = 0.;
  fPdgCode = 0;
  
}

//___________________________________________________________

void
AliAnalysisPIDParticle::Update(TParticle *particle, Int_t label)
{
  /*
   * update
   */

  fLabel = label;
  fPt = particle->Pt();
  fEta = particle->Eta();
  fPhi = particle->Phi();
  fPdgCode = particle->GetPdgCode();
  
}

