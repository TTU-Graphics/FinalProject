{
  "models": [
    /*{
      "type": "model",
      "id": "sponge",
      "class": "Menger",
      "center": [0,0,0],
      "radius": 1,
      "subdivisions": 2
    },//*/
    {
      "type": "model",
      "id": "particles",
      "class": "Particles",
      "number": 20
    },
    {
      "type": "model",
      "id": "foreground_grass",
      "class": "ObjModel",
      "objfile": "objects/grass_low.obj",
      "ambient": [1,1,1,1],
      "diffuse": [1,1,1,1],
      "specular": [1,1,1,1]
    },//*/
    {
      "type": "model",
      "id": "hat",
      "class": "ObjModel",
      "objfile": "objects/wizardHatFinal.obj",
      "ambient": [1,1,1,1],
      "diffuse": [1,1,1,1],
      "specular": [1,1,1,1]
    },//*/
    {
      "type": "model",
      "id": "curtain",
      "class": "ObjModel",
      "objfile": "objects/curtain_low.obj",
      "ambient": [1,1,1,1],
      "diffuse": [1,1,1,1],
      "specular": [1,1,1,1]
    },//*/
    {
      "type": "model",
      "id": "stage_floor",
      "class": "ObjModel",
      "objfile": "objects/plywood.obj",
      "ambient": [1,1,1,1],
      "diffuse": [1,1,1,1],
      "specular": [1,1,1,1]
    },
    {
      "type": "model",
      "id": "backdrop",
      "class": "ObjModel",
      "objfile": "objects/backdrop_low.obj",
      "ambient": [1,1,1,1],
      "diffuse": [1,1,1,1],
      "specular": [1,1,1,1]
    },//*/
    {
      "type": "model",
      "id": "mountains",
      "class": "ObjModel",
      "objfile": "objects/mountains_low.obj",
      "ambient": [1,1,1,1],
      "diffuse": [1,1,1,1],
      "specular": [1,1,1,1]
    },//*/
    {
      "type": "model",
      "id": "bird1",
      "class": "ObjModel",
      "objfile": "objects/bird.obj",
      "ambient": [1,1,1,1],
      "diffuse": [1,1,1,1],
      "specular": [1,1,1,1]
    },//*/
    {
      "type": "model",
      "id": "machine",
      "class": "ObjModel",
      "objfile": "objects/mysteryMachineCore.obj",
      "ambient": [1,1,1,1],
      "diffuse": [1,1,1,1],
      "specular": [1,1,1,1]
    },//*/
    {
      "type": "model",
      "id": "ruby_face",
      "class": "ObjModel",
      "objfile": "objects/rubyFace.obj",
      "ambient": [1,1,1,1],
      "diffuse": [1,1,1,1],
      "specular": [1,1,1,1]
    },//*/
    {
      "type": "model",
      "id": "wizard",
      "class": "ObjModel",
      "objfile": "objects/wizardFace.obj",
      "ambient": [1,1,1,1],
      "diffuse": [1,1,1,1],
      "specular": [1,1,1,1]
    },//*/
    /*{
      "type": "model",
      "id": "ruby_bow",
      "class": "ObjModel",
      "objfile": "objects/rubysBow.obj",
      "ambient": [1,1,1,1],
      "diffuse": [1,1,1,1],
      "specular": [1,1,1,1]
    },//*/
    {
      "type": "model",
      "id": "stick1",
      "class": "ObjModel",
      "objfile": "objects/stick.obj",
      "ambient": [1,1,1,1],
      "diffuse": [1,1,1,1],
      "specular": [1,1,1,1]
    },
    {
      "type": "model",
      "class": "Tesseract",
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
    }/*,
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
    }//*/
  ],
  "instances": [
    {
      "reference": "curtain",
      "translate": [-6,0,0]
    }, {
      "reference": "curtain",
      "translate": [-5.5,4.5,-0.5]
    }, {
      "reference": "curtain",
      "translate": [-4.5,4.5,-0.5]
    }, {
      "reference": "curtain",
      "translate": [-3.5,4.5,-0.5]
    }, {
      "reference": "curtain",
      "translate": [-2.5,4.5,-0.5]
    }, {
      "reference": "curtain",
      "translate": [-1.5,4.5,-0.5]
    }, {
      "reference": "curtain",
      "translate": [-0.5,4.5,-0.5]
    }, {
      "reference": "stick1",
      "translate": [2.35,0.4,0]
    }
  ],
  "animations": [
    {
      "type": "physics",
      "object": "particles"
    },
    {
      "type": "orbit",
      "center": "plastic",
      "orbiter": "particles",
      "distance": 0,
      "theta": 0,
      "phi": 0
    },
    {
      "type": "controlled",
      "object": "ruby_face",
      "limit": [10,0,1],
      "speed": 0.5
    },
    {
      "type": "orbit",
      "center": "ruby_face",
      "orbiter": "stick1",
      "distance": 0,
      "theta": 0,
      "phi": 0
    },
    /*{
      "type": "orbit",
      "center": "ruby_face",
      "orbiter": "ruby_bow",
      "distance": 1,
      "theta": 0,
      "phi": 0
    },//*/
    {
      "type": "orbit",
      "center": "wizard",
      "orbiter": "metal",
      "distance": 2,
      "theta": 30,
      "phi": 0
    },
    {
      "type": "oscillate",
      "object": "plastic",
      "max": [0.05,0.05,0],
      "rate": [0.007,0.01,0.0],
      "center": [1.4,2.22,0.2]
    },
    {
      "type": "oscillate",
      "object": "bird1",
      "max": [3,0.5,0],
      "rate": [0.05,0.01,0.0],
      "center": [0,1,0]
    }
    /*, {
      "type": "oscillate",
      "object": "curtain",
      "max": [3,0,0],
      "rate": [0.02,0.0,0.0],
      "center": [-4,0,0]
    }//*/
    /* {
      "type": "orbit",
      "center": "plastic",
      "orbiter": "metal",
      "distance": 2.1,
      "theta": 40,
      "phi": 0 
    }, {
      "type": "orbit",
      "center": "hat",
      "orbiter": "matte",
      "distance": 2.1,
      "theta": 40,
      "phi": 0 
    }, {
      "type": "oscillate",
      "object": "matte",
      "max": [0.5,0.5,0.5],
      "rate": [0.02,0.01,0.05],
      "center": [1,1,1]
    },*//* {
      "type": "oscillate",
      "object": "stage_floor",
      "max": [0.0,0.5,0.0],
      "rate": [0.0,0.0,0.0],
      "center": [0,-0.5,0]
    }, *//*{
      "type": "orbit",
      "center": "hat",
      "orbiter": "textri",
      "distance": 7.5,
      "theta": 0,
      "phi": 50
    },*//* {
      "type": "orbit",
      "center": "hat",
      "orbiter": "ruby_bow",
      "distance": 4,
      "theta": 25,
      "phi": 50
    }, {
      "type": "orbit",
      "center": "ruby_bow",
      "orbiter": "stick1",
      "distance": 2,
      "theta": -30,
      "phi": 0
    }*/
  ],
  "lights": [
    {
      "center": [3,0,5,0],
      "ambient": [0.3,0.3,0.3,1],
      "diffuse": [0.4,0.4,0.4,1],
      "specular": [0.4,0.4,0.4,1]
    }, //*/
    {
      "center": [5,15,1,0],
      "ambient": [0,0,0,1],
      "diffuse": [0.1,0.2,1,1],
      "specular": [0.3,1,1,1]
    },//*/
    {
      "center": [0,4,10,0],
      "ambient": [0.0,0.0,0.0,1],
      "diffuse": [0.6,0.6,0.6,1],
      "specular": [0.6,0.6,0.6,1]
    },
    {
      "center": [5,4,3,0],
      "ambient": [0.0,0.0,0.0,1],
      "diffuse": [1,0,0,1],
      "specular": [1,0,0,1],
      "direction": [-1,-1,-1,0],
      "angle": 45
    }/*,
    {
      "center": [2,0,5,0],
      "ambient": [0.0,0.0,0.0,1],
      "diffuse": [1,1,1,1],
      "specular": [1,1,1,1],
      "direction": [-2,0,-5,0],
      "angle": 15
    }*/
  ],
  "camera": {
    "type": "projection",
    "fovy": 45,
    "zNear": 0.5,
    "zFar": 50,
    "radius": 15,
    "theta": 0,
    "phi": 3.14
  }
}
