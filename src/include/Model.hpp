#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>

#include "Model.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

/**
 * @class Model
 * @brief Model consisting of multiple meshes.
 */
class Model : public Transformable {
private:
    /// A vector containing pointers to the meshes of the model.
    std::vector<Mesh*> meshes;

public:
    /**
     * @brief Destructor for Model.
     * Deletes model meshes.
     */
    ~Model();

    /**
     * @brief Loads the model from a file.
     * @param path The file path to load the model from.
     *
     * @note OBJ is currently an only supported format.
     */
    void load(const std::string& path);

    /**
     * @brief Gets the meshes of the model.
     * @return A vector of pointers to the meshes.
     */
    std::vector<Mesh*> getMeshes();

    /**
     * @brief Sets the diffuse texture for all meshes in the model.
     * @param path The file path to the diffuse texture.
     */
    void setDiffuseTexture(const char* path);

    /**
     * @brief Sets the specular texture for all meshes in the model.
     * @param path The file path to the specular texture.
     */
    void setSpecularTexture(const char* path);

    /**
     * @brief Sets the shininess for all meshes in the model.
     * @param shininess The shininess value.
     */
    void setShininess(GLfloat shininess);

    /**
     * @brief Sets the texture scale for all meshes in the model.
     * @param scaleX The scale factor in the X direction.
     * @param scaleY The scale factor in the Y direction.
     */
    void setTextureScale(float scaleX, float scaleY);

    /**
     * @brief Sets whether all meshes in the model should ignore lighting.
     * @param ignore Whether to ignore lighting.
     */
    void setIgnoreLight(bool ignore);

    /**
     * @brief Sets whether all meshes in the model are view independent.
     * @param independent Whether the meshes are view independent.
     */
    void setViewIndependent(bool independent);

    /**
     * @brief Sets whether all meshes in the model are in the foreground.
     * @param foreground Whether the meshes are in the foreground.
     */
    void setOnForeground(bool foreground);

    /**
     * @brief Sets the position of the model.
     * @param position The new position as 3D vector.
     */
    void setPosition(glm::vec3 position) override;

    /**
     * @brief Sets the position of all model meshes.
     * @param x The X coordinate of the new position.
     * @param y The Y coordinate of the new position.
     * @param z The Z coordinate of the new position.
     */
    void setPosition(GLfloat x, GLfloat y, GLfloat z) override;

    /**
     * @brief Moves all model meshes by a given translation.
     * @param x The translation in the X direction.
     * @param y The translation in the Y direction.
     * @param z The translation in the Z direction.
     */
    void move(GLfloat x, GLfloat y, GLfloat z) override;

    /**
     * @brief Moves all model meshes by a given translation.
     * @param translation The translation as 3D vector.
     */
    void move(glm::vec3 translation) override;

    /**
     * @brief Sets the rotation of all model meshes.
     * @param angleDegrees The rotation angle in degrees.
     * @param x The X component of the rotation axis.
     * @param y The Y component of the rotation axis.
     * @param z The Z component of the rotation axis.
     */
    void setRotation(GLfloat angleDegrees, GLfloat x, GLfloat y, GLfloat z) override;

    /**
     * @brief Sets the rotation of all model meshes.
     * @param angleDegrees The rotation angle in degrees.
     * @param origin The rotation axis as 3D vector.
     */
    void setRotation(GLfloat angleDegrees, glm::vec3 origin) override;

    /**
     * @brief Rotates all model meshes.
     * @param angleDegrees The rotation angle in degrees.
     * @param x The X component of the rotation axis.
     * @param y The Y component of the rotation axis.
     * @param z The Z component of the rotation axis.
     */
    void rotate(GLfloat angleDegrees, GLfloat x, GLfloat y, GLfloat z) override;

    /**
     * @brief Rotates all model meshes.
     * @param angleDegrees The rotation angle in degrees.
     * @param origin The rotation axis as 3D vector.
     */
    void rotate(GLfloat angleDegrees, glm::vec3 origin) override;

    /**
     * @brief Sets the scale of all model meshes.
     * @param x The scale factor in the X direction.
     * @param y The scale factor in the Y direction.
     * @param z The scale factor in the Z direction.
     */
    void setScale(GLfloat x, GLfloat y, GLfloat z) override;

    /**
     * @brief Sets the scale of all model meshes.
     * @param scale The scale factors as 3D vector.
     */
    void setScale(glm::vec3 scale) override;

    /**
     * @brief Scales the all model meshes.
     * @param x The scale factor in the X direction.
     * @param y The scale factor in the Y direction.
     * @param z The scale factor in the Z direction.
     */
    void scale(GLfloat x, GLfloat y, GLfloat z) override;

    /**
     * @brief Scales all model meshes.
     * @param scale The scale factors as 3D vector.
     */
    void scale(glm::vec3 scale) override;
};

#endif
