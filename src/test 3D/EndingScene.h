#pragma once
#include "MainClass.h"

class EndingScene : public MainClass
{
public:

public:
	virtual bool Init()		noexcept override;
	virtual bool Frame()	noexcept override;
	virtual bool Render()	noexcept override;
	virtual bool Release()	noexcept override;

	EndingScene() = default;
	virtual ~EndingScene() = default;
};