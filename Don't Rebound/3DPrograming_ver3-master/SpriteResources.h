#pragma once

class SpriteResources
{
public:
	static SpriteResources *GetInstance()
	{
		s_SpriteResources = s_SpriteResources ? s_SpriteResources : Create();
		return s_SpriteResources;
	}

	static SpriteResources* Create();
	static void Destroy();

	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_sprites;

	// �X�v���C�g�t�H���g
	std::unique_ptr<DirectX::SpriteFont> m_font;

protected:
	static SpriteResources *s_SpriteResources;
};
