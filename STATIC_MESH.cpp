#include "../pipiLib/pch.h"
#include "../pipiLib/GRAPHIC.h"
#include "STATIC_MESH.h"

STATIC_MESH::STATIC_MESH()
{
	create();
}

STATIC_MESH::~STATIC_MESH()
{
	ConstBuf1->Unmap(0, nullptr);
	ConstBuf2->Unmap(0, nullptr);
}

void STATIC_MESH::create()
{
	auto& g = GRAPHIC::instance();
	//���_�o�b�t�@������
	{
		//���f�[�^
		float vertices[] = {
			//position           normal             texcoord
			-0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,//����
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,//����
			 0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,//�E��
			 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,//�E��
		};
		g.createVertexBuf(vertices, sizeof(vertices), 4*8, &VertexBuf, &Vbv);
	}
	//���_�C���f�b�N�X�o�b�t�@������
	{
		unsigned short indices[] = {
			0,1,2,
			3,2,1,
		};
		g.createIndexBuf(indices, sizeof(indices), &IndexBuf, &Ibv);

	}
	//�R���X�^���g�o�b�t�@�P������
	{
		g.createConstBuf(sizeof(GRAPHIC::CONST_BUF1), &ConstBuf1, (void**)&ConstBuf1Map);
	}
	//�R���X�^���g�o�b�t�@�Q������
	{
		g.createConstBuf(sizeof(GRAPHIC::CONST_BUF2), &ConstBuf2, (void**)&ConstBuf2Map);
		ConstBuf2Map->diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
		ConstBuf2Map->ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
	}
	//�e�N�X�`���o�b�t�@������
	{
		LPCWSTR filename = L"assets/penguin2.png";
		g.createTextureBuf(filename, &TextureBuf);
	}
	//�f�B�X�N���v�^�q�[�v������
	{
		g.createCbvTbvHeap(ConstBuf1.Get(), ConstBuf2.Get(), TextureBuf.Get(), &CbvTbvHeap);
	}
}

void STATIC_MESH::update(const MATRIX& world)
{
	ConstBuf1Map->world = world;
}

void STATIC_MESH::draw()
{
	auto& g = GRAPHIC::instance();
	g.draw(Vbv,Ibv,CbvTbvHeap.Get());
}
