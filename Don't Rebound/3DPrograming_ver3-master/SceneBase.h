#pragma once
class SceneBase {
public:
	//�������z�֐��Ƃ��Ď���
	virtual void Initialize() = 0;
	virtual void update() = 0;
	virtual void Render() = 0;


};