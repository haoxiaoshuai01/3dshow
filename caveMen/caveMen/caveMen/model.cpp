#include "../../includes/learnopengl/model.h"

Model::Model(Model & other)
{
	this->textures_loaded = other.textures_loaded;
	this->meshes = other.meshes;
	this->directory = other.directory;
	this->gammaCorrection = other.gammaCorrection;
	this->modelMatrix = other.modelMatrix;
	this->postion = other.postion;
	
}
Model::Model(string const &path, Shader* shader, Shader* lineshader, glm::mat4 *project, glm::mat4 *lookat, bool gamma ) :CObject(), gammaCorrection(gamma)
{
	mShader = shader;
	mLookat = lookat;
	mProject = project;
	mlineShader = lineshader;
	this->actorType = EActorType::eModel;
	loadModel(path);

	Eigen::Matrix<float, Eigen::Dynamic, 3> m;


	int i = 0;
	for (auto item : meshes)
	{
		i = i + item.vertices.size();
	}
	m.resize(i, 3);

	i = 0;
	for (auto item : meshes)
	{
		for (auto v : item.vertices)
		{
			m(i, 0) = v.Position.x;
			m(i, 1) = v.Position.y;
			m(i, 2) = v.Position.z;
			i++;
		}
	}

	genboundingbox(m);
	addBox();
	update();
}

void Model::update()
{
	CObject::update();
	for (auto item : drawLineWidth1s)
		item->modelMatrix = this->modelMatrix;
}

void Model::Draw()
{
	mShader->use();
	mShader->setMat4("projection", *mProject);
	mShader->setMat4("view", *mLookat);
	mShader->setMat4("model", modelMatrix);
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Draw(*mShader);

	for (auto item : drawLineWidth1s)
	{
		
		item->Draw();
	}
	
}

void Model::addBox()
{
	if (drawLineWidth1s.size() > 0)
	{
		for (auto item : drawLineWidth1s)
			delete item;
	}
	/*glm::vec4 ming = modelMatrix * glm::vec4(boundingboxMin.x(),boundingboxMin.y(),boundingboxMin.z(),1.0f) ;
	glm::vec4 maxg = modelMatrix * glm::vec4(boundingboxMax.x(), boundingboxMax.y(), boundingboxMax.z(), 1.0f);

	ming = ming / ming[3];
	maxg = maxg / maxg[3];*/
	Eigen::Vector3f min_(boundingboxMin[0], boundingboxMin[1], boundingboxMin[2]);
	Eigen::Vector3f max_(boundingboxMax[0], boundingboxMax[1], boundingboxMax[2]);

	drawLineWidth1s.push_back(new CLinewidth1(vec3(min_(0), min_(1), min_(2)), vec3(max_(0), min_(1), min_(2)),mlineShader,mProject,mLookat));
	drawLineWidth1s.push_back(new CLinewidth1(vec3(min_(0), min_(1), min_(2)), vec3(min_(0), max_(1), min_(2)),mlineShader,mProject,mLookat));
	drawLineWidth1s.push_back(new CLinewidth1(vec3(min_(0), max_(1), min_(2)), vec3(max_(0), max_(1), min_(2)),mlineShader,mProject,mLookat));
																											 
	drawLineWidth1s.push_back(new CLinewidth1(vec3(max_(0), max_(1), min_(2)), vec3(max_(0), min_(1), min_(2)),mlineShader,mProject,mLookat));
	drawLineWidth1s.push_back(new CLinewidth1(vec3(min_(0), min_(1), min_(2)), vec3(min_(0), min_(1), max_(2)),mlineShader,mProject,mLookat));
																											 
	drawLineWidth1s.push_back(new CLinewidth1(vec3(max_(0), max_(1), max_(2)), vec3(max_(0), max_(1), min_(2)),mlineShader,mProject,mLookat));
	drawLineWidth1s.push_back(new CLinewidth1(vec3(max_(0), max_(1), max_(2)), vec3(min_(0), max_(1), max_(2)),mlineShader,mProject,mLookat));
	drawLineWidth1s.push_back(new CLinewidth1(vec3(max_(0), max_(1), max_(2)), vec3(max_(0), min_(1), max_(2)),mlineShader,mProject,mLookat));
																											 
	drawLineWidth1s.push_back(new CLinewidth1(vec3(max_(0), min_(1), max_(2)), vec3(min_(0), min_(1), max_(2)),mlineShader,mProject,mLookat));
	drawLineWidth1s.push_back(new CLinewidth1(vec3(min_(0), max_(1), max_(2)), vec3(min_(0), min_(1), max_(2)),mlineShader,mProject,mLookat));
																											  
	drawLineWidth1s.push_back(new CLinewidth1(vec3(max_(0), min_(1), max_(2)), vec3(max_(0), min_(1), min_(2)),mlineShader,mProject,mLookat));
	drawLineWidth1s.push_back(new CLinewidth1(vec3(min_(0), max_(1), max_(2)), vec3(min_(0), max_(1), min_(2)),mlineShader,mProject,mLookat));


	
}

void Model::addAxies()
{
	

}

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma)
{
	string filename = string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}