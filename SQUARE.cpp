#include "../pipiLib/pch.h"
#include "../pipiLib/GRAPHIC.h"
#include "SQUARE.h"

SQUARE::SQUARE(LPCWSTR filename)
{
	create(filename);
}

SQUARE::~SQUARE()
{
	ConstBuf1->Unmap(0, nullptr);
	ConstBuf2->Unmap(0, nullptr);
}

void SQUARE::create(LPCWSTR filename)
{
	auto& g = GRAPHIC::instance();
	//���_�o�b�t�@�A�ʒu������
	{
		//�ʒu�̐��f�[�^
		float positions[] = {
			-0.5f,  0.5f, 0.0f,//����
			-0.5f, -0.5f, 0.0f,//����
			 0.5f,  0.5f, 0.0f,//�E��
			 0.5f, -0.5f, 0.0f,//�E��
		};
		g.createVertexBuf(positions, sizeof(positions), 4*3, &PositionBuf, &PositionBufView);
	}
	//���_�o�b�t�@�A�@���x�N�g��������
	{
		//�@���̐��f�[�^
		float normals[] = {
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
		};
		g.createVertexBuf(normals, sizeof(normals), 4*3, &NormalBuf, &NormalBufView);
	}
	//���_�o�b�t�@�A�e�N�X�`�����W������
	{
		//�e�N�X�`�����W�̐��f�[�^
		float texcoords[] = {
			0.0f, 0.0f,//����
			0.0f, 1.0f,//����
			1.0f, 0.0f,//�E��
			1.0f, 1.0f,//�E��
		};
		g.createVertexBuf(texcoords, sizeof(texcoords), 4*2, &TexcoordBuf, &TexcoordBufView);
	}
	//���_�C���f�b�N�X�o�b�t�@������
	{
		unsigned short indices[] = {
			0,1,2,
			3,2,1,
		};
		g.createIndexBuf(indices, sizeof(indices), &IndexBuf, &IndexBufView);

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
		g.createTextureBuf(filename, &TextureBuf);
	}
	//�f�B�X�N���v�^�q�[�v������
	{
		g.createCbvTbvHeap(ConstBuf1.Get(), ConstBuf2.Get(), TextureBuf.Get(), &CbvTbvHeap);
	}
}

void SQUARE::update(const MATRIX& world)
{
	ConstBuf1Map->world = world;
}

void SQUARE::draw()
{
	auto& g = GRAPHIC::instance();
	g.draw(
		PositionBufView,
		NormalBufView,
		TexcoordBufView,
		IndexBufView,
		CbvTbvHeap.Get()
	);
}
