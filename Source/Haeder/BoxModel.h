#pragma once

#include "../Haeder/DxLibBox.h"
#include <map>
#include <string>

class BoxModel
{
private:
	std::map<std::string, DxLibBox> m_boxMap;

public:
	BoxModel();
	virtual ~BoxModel();

	//Box‚Ì’Ç‰Á
	void AddBox(std::string tag, DxLibBox& box, std::string parentName = "");

	//Box‚ÌŽæ“¾
	DxLibBox* GetBox(std::string tag);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};