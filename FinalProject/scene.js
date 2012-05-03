{
  "models": [
    {
      "type": "model",
      "id": "sponge",
      /*"class": "Menger",
      "center": [0,0,0],
      "radius": 1,
      "subdivisions": 2*/
      "class": "ObjModel",
      "objfile": "objects/WizardHat.obj",
      "ambient": [1,1,1,1],
      "diffuse": [1,1,1,1],
      "specular": [1,1,1,1]
    },
    {
      "type": "model",
      "class": "Sphere",
      "id": "plastic",
      "subdivs": 4,
      "radius": 1,
      "ambient": [0.7,0.1,0.1,1],
      "diffuse": [0.5,0.2,0.2,1],
      "specular": [0.8,0.7,0.7,1]
    },
    {
      "type": "model",
      "class": "Sphere",
      "id": "metal",
      "subdivs": 4,
      "ambient": [0.3,0.3,0.3,1],
      "diffuse": [0.7,0.7,0.7,1],
      "specular": [1,1,1,1],
      "radius": 0.6
    },
    {
      "type": "model",
      "class": "Sphere",
      "id": "matte",
      "subdivs": 4,
      "radius": 0.7,
      "ambient": [0.1,0.7,0.1,1],
      "diffuse": [0.2,1,0.2,1],
      "specular": [0,0,0,1]
    },
    {
      "type": "model",
      "class": "TexTri",
      "id": "textri",
      "texture": "uv_checker.png"
    }
  ],
  "animations": [
    {
      "center": "sponge",
      "orbiter": "plastic",
      "distance": 3.5,
      "theta": 0,
      "phi": 20
    }, {
      "center": "plastic",
      "orbiter": "metal",
      "distance": 2.1,
      "theta": 40,
      "phi": 0
    }, {
      "center": "sponge",
      "orbiter": "matte",
      "distance": 5.6,
      "theta": -20,
      "phi": 0 
    }, {
      "center": "sponge",
      "orbiter": "textri",
      "distance": 7.5,
      "theta": 0,
      "phi": 50
    }
  ],
  "lights": [
    {
      "center": [3,0,0,0],
      "ambient": [0.2,0.2,0.5,1],
      "diffuse": [0.2,0.4,1,1],
      "specular": [1,1,0.8,1]
    }, {
      "center": [0,1,0,0],
      "ambient": [0.2,0.4,0.2,1],
      "diffuse": [0.1,0.2,1,1],
      "specular": [0.3,1,1,1]
    }
  ],
  "camera": {
    "type": "projection",
    "fovy": 45,
    "zNear": 0.5,
    "zFar": 50,
    "radius": 15,
    "theta": 0,
    "phi": 0
  }
}
