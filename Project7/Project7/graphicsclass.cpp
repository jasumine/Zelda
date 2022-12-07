////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;

	m_ModelHouse = 0;
	m_ModelGround = 0;
	m_ModelTree = 0;
	m_ModelCharacter = 0;
	m_ModelTable = 0;
	m_ModelBed = 0;
	m_ModelLantern = 0;
	m_ModelLight = 0;

	m_LightShader = 0;
	m_Light = 0;

	m_TextureShader = 0;
	m_Bitmap = 0;

}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, 0.0f);	// for chair
	
	// ============================model=====================================

	// House
	m_ModelHouse = new ModelClass;
	if (!m_ModelHouse)
	{
		return false;
	}

	// Initialize the model object.
	 result = m_ModelHouse->Initialize(m_D3D->GetDevice(), L"./data/house2.obj", L"./data/seafloor.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	
	// Ground
	m_ModelGround = new ModelClass;
	if (!m_ModelGround)
	{
		return false;
	}

	result = m_ModelGround->Initialize(m_D3D->GetDevice(), L"./data/ground.obj", L"./data/ground.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model ground object.", L"Error", MB_OK);
		return false;
	}
	
	// Tree
	m_ModelTree = new ModelClass;
	if (!m_ModelTree)
	{
		return false;
	}

	result = m_ModelTree->Initialize(m_D3D->GetDevice(), L"./data/tree2.obj", L"./data/ground.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model ground object.", L"Error", MB_OK);
		return false;
	}

	// Character
	m_ModelCharacter = new ModelClass;
	if (!m_ModelCharacter)
	{
		return false;
	}

	result = m_ModelCharacter->Initialize(m_D3D->GetDevice(), L"./data/link.obj", L"./data/link.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model ground object.", L"Error", MB_OK);
		return false;
	}

	// Table
	m_ModelTable = new ModelClass;
	if (!m_ModelCharacter)
	{
		return false;
	}

	result = m_ModelTable->Initialize(m_D3D->GetDevice(), L"./data/table.obj", L"./data/table.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model ground object.", L"Error", MB_OK);
		return false;
	}
	/*
	// Bed
	m_ModelBed = new ModelClass;
	if (!m_ModelBed)
	{
		return false;
	}

	result = m_ModelBed->Initialize(m_D3D->GetDevice(), L"./data/bed.obj", L"./data/bed.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model ground object.", L"Error", MB_OK);
		return false;
	}
	*/

	// lantern
	m_ModelLantern = new ModelClass;
	if (!m_ModelLantern)
	{
		return false;
	}

	result = m_ModelLantern->Initialize(m_D3D->GetDevice(), L"./data/lantern.obj", L"./data/lantern.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model ground object.", L"Error", MB_OK);
		return false;
	}

	// light
	m_ModelLight = new ModelClass;
	if (!m_ModelLight)
	{
		return false;
	}

	result = m_ModelLight->Initialize(m_D3D->GetDevice(), L"./data/light.obj", L"./data/light.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model ground object.", L"Error", MB_OK);
		return false;
	}

	// =================================================================

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
//	m_Light->SetAmbientColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
//	m_Light->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
//	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
//	m_Light->SetDirection(1.0f, 0.0f, 0.0f);
	m_Light->SetDirection(1.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	/*
	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"./data/ground.dds", 1000,1000);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}
	*/
	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the model object.
	if(m_ModelHouse)
	{
		m_ModelHouse->Shutdown();
		delete m_ModelHouse;
		m_ModelHouse = 0;
	}

	if (m_ModelGround)
	{
		m_ModelGround->Shutdown();
		delete m_ModelGround;
		m_ModelGround = 0;
	}

	if (m_ModelTree)
	{
		m_ModelTree->Shutdown();
		delete m_ModelTree;
		m_ModelTree = 0;
	}

	if (m_ModelCharacter)
	{
		m_ModelCharacter->Shutdown();
		delete m_ModelCharacter;
		m_ModelCharacter = 0;
	}

	if (m_ModelTable)
	{
		m_ModelTable->Shutdown();
		delete m_ModelTable;
		m_ModelTable = 0;
	}

	if (m_ModelBed)
	{
		m_ModelBed->Shutdown();
		delete m_ModelBed;
		m_ModelBed = 0;
	}

	if (m_ModelLantern)
	{
		m_ModelLantern->Shutdown();
		delete m_ModelLantern;
		m_ModelLantern = 0;
	}

	if (m_ModelLight)
	{
		m_ModelLight->Shutdown();
		delete m_ModelLight;
		m_ModelLight = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	
	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	return;
}

bool GraphicsClass::Frame(float positionX, float positionZ, float rotationX, float rotationY, int fps, int cpu)
{
	bool result;

	// 카메라 위치 설정
	m_Camera->SetPosition(positionX, 0.0f, -positionZ);

	// 카메라의 회전을 설정합니다
	m_Camera->SetRotation(rotationX, rotationY, 0.0f);

	/*
	// Update the rotation variable each frame.
	rotation += XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if(!result)
	{
		return false;
	}
	*/
	return true;
}

bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;
	
	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();
	/*
	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 0,0, 120);
	if (!result)
	{
		return false;
	}

	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	if (!result)
	{
		return false;
	}
	*/
	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	worldMatrix = XMMatrixIdentity();

	// =====================Model========================

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	
	// House
	m_ModelHouse->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_ModelHouse->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_ModelHouse->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	
	// Ground
	worldMatrix *= XMMatrixScaling(3, 0.1f, 3);
	worldMatrix *= XMMatrixTranslation(0, -1.0f, 0);

	m_ModelGround->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_ModelGround->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_ModelGround->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	
	// Tree
	XMMATRIX worldMatrix_Tree;
	worldMatrix_Tree = XMMatrixIdentity();
	worldMatrix_Tree *= XMMatrixScaling(20, 20, 20);
	worldMatrix_Tree *= XMMatrixTranslation(-50, 0, 0);
	m_ModelTree->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_ModelTree->GetIndexCount(),
		worldMatrix_Tree, viewMatrix, projectionMatrix,
		m_ModelTree->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	
	// Character
	XMMATRIX worldMatrix_Character;
	worldMatrix_Character = XMMatrixIdentity();
	worldMatrix_Character *= XMMatrixScaling(0.0012f, 0.0012f, 0.0012f);
	worldMatrix_Character *= XMMatrixTranslation(0, 0, -50);

	m_ModelCharacter->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_ModelCharacter->GetIndexCount(),
		worldMatrix_Character, viewMatrix, projectionMatrix,
		m_ModelCharacter->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	
	// Table

	XMMATRIX worldMatrix_Table;
	worldMatrix_Table = XMMatrixIdentity();
	worldMatrix_Table *= XMMatrixScaling(15, 15, 15);
	worldMatrix_Table *= XMMatrixTranslation(-10.0f, -1.0f, 0.0f);

	m_ModelTable->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_ModelTable->GetIndexCount(),
		worldMatrix_Table, viewMatrix, projectionMatrix,
		m_ModelTable->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	
	/*
	// Bed
	XMMATRIX worldMatrix_Bed;
	worldMatrix_Bed = XMMatrixIdentity();
	worldMatrix_Bed *= XMMatrixScaling(30.0f, 30.0f, 30.0f);
	worldMatrix_Bed *= XMMatrixTranslation(0, -1.0f, 0);
	worldMatrix_Bed *= XMMatrixRotationX(45);
	// worldMatrix_Bed *= XMMatrixRotationY(45);
	worldMatrix_Bed *= XMMatrixRotationZ(45);

	m_ModelBed->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_ModelBed->GetIndexCount(),
		worldMatrix_Bed, viewMatrix, projectionMatrix,
		m_ModelBed->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	*/

	// lantern
	XMMATRIX worldMatrix_Lantern;
	worldMatrix_Lantern = XMMatrixIdentity();
	// worldMatrix_Lantern *= XMMatrixScaling(30.0f, 30.0f, 30.0f);
	worldMatrix_Lantern *= XMMatrixTranslation(0, 10.0f, 0);

	m_ModelLantern->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_ModelLantern->GetIndexCount(),
		worldMatrix_Lantern, viewMatrix, projectionMatrix,
		m_ModelLantern->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	

	// light
	XMMATRIX worldMatrix_Light;
	worldMatrix_Light = XMMatrixIdentity();
	 worldMatrix_Light *= XMMatrixScaling(10.0f, 10.0f, 10.0f);
	worldMatrix_Light *= XMMatrixTranslation(0, 50.0f, 0);

	
	m_ModelLight->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_ModelLight->GetIndexCount(),
		worldMatrix_Light, viewMatrix, projectionMatrix,
		m_ModelLight->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	
	// =======================================================
	
	if(!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

