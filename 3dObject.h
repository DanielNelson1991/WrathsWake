#pragma once
class CGame;
class CBoundingSphere; 

class C3dObject  
{
protected:
	float m_fX;	//the position of the centre of the 3dObject
	float m_fY;
	float m_fZ;
	float m_fW;	//width of the 3dObject in arbitrary units
	float m_fH;	//height of the 3dObject in arbitrary units
	float m_fD;
	int m_iTextureID; //which of the preloaded textures to use

	float m_fR;	//red component between 0 and 1
	float m_fG;	//green component between 0 and 1
	float m_fB;	//blue component between 0 and 1
	float m_fA;	//alpha value 0-1

	bool m_bEnableCollisions; // Enabling collision for 3DObjects
	bool m_bClampToTerrain;	// Is this object clamped to the terrain?
	float m_fClampOffset;	// If yes, how much by?


	float m_fYaw;
	float m_fPitch;
	float m_fRoll;

	CBoundingSphere * m_pBSphere;
	virtual void CalcBoundingSphere(); 


	bool m_bInsideOut;
	bool m_bLighting;

public:
	C3dObject();
	C3dObject( float x, float y, float z, float w=1.0, float h=1.0,float d=1.0, int textureID=1); 

	virtual ~C3dObject();
	virtual void Render();
	virtual void PostRender(){;};
	virtual void Update(float dt_);

	
	virtual bool RespondToCollision(C3dObject * hitObject); //bool return value false means block, true means pass through
	
	void SetYaw(float yaw_){m_fYaw=yaw_;}
	void SetPosition(float x_,float y_,float z_);

	void IncrementYaw(float dyaw_);
	void IncrementPitch(float dpitch_);
	void ApplyClampToTerrain();

	// Terrain Clamping
	void SetClampOffset(float offset) {m_fClampOffset = offset;}
	void SetClampToTerrain(bool onoff) {m_bClampToTerrain=onoff;}

	// Collisions
	void SetEnableCollisions(bool onoff_) {m_bEnableCollisions=onoff_;}
	void SetVelocity(float vx,float vy,float vz);
	bool GetEnableCollisions(){return m_bEnableCollisions;}

	float Getx(){return m_fX;}
	float Gety(){return m_fY;}
	float Getz(){return m_fZ;}
	float Getw(){return m_fW;}
	float Geth(){return m_fH;}
	float Getd(){return m_fD;}
	float m_fDistanceFromViewpoint;

	CBoundingSphere * GetBoundingSphere(){return m_pBSphere;} //needs to be in public section

	float m_fVelocityx;
	float m_fVelocityy;
	float m_fVelocityz;
	bool bUseGravity;
	bool bTaggedForDeletion;

	virtual void HitByBullet();

	virtual bool isColliding(CBoundingSphere * bsphere_);

private:
	
}; 

