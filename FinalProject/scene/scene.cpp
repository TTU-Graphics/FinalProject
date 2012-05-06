#include "scene.h"

Scene::Scene(const char* sceneFile) {
  //*
  Json::Value root;
  Json::Reader reader;
  filebuf fb;
  fb.open(sceneFile,ios::in);
  istream json(&fb);
  if(!reader.parse(json, root)) {
    printf("error parsing scene file!!! %s\n%s\n",sceneFile,
        reader.getFormatedErrorMessages().c_str());
    return;
  }
  fb.close();

  buildScene(root);

  /*Menger *m = new Menger(vec3(0,0,0), 1, 2);
    models.push_back(m);*/
}

//{{{1 public functions
void Scene::tick(float seconds) {
  //animator->step(seconds);
  vector<Animation*>::iterator it;
  for(it = animations.begin(); it != animations.end(); it++) {
    (*it)->step(seconds);
  }
}

void Scene::setWorldMatrix(mat4 mat) {
  vector<Model*>::iterator modelIterator;
  for(modelIterator = models.begin(); modelIterator != models.end(); modelIterator++) {
    (*modelIterator)->setWorldMatrix(mat);
  }
}

void Scene::setProjection(mat4 mat) {
  vector<Model*>::iterator modelIterator;
  for(modelIterator = models.begin(); modelIterator != models.end(); modelIterator++) {
    (*modelIterator)->setProjection(mat);
  }
}

void Scene::render() {
  vector<Model*>::iterator modelIterator;
  for(modelIterator = models.begin(); modelIterator != models.end(); modelIterator++) {
    (*modelIterator)->render();
  }
}
//}}}1
//{{{1 private functions
void Scene::buildScene(Json::Value node) {
  Json::Value cam = node["camera"];
  buildCamera(cam);

  Json::Value lights = node["lights"];
  for(int i=0;i<lights.size();i++) {
    buildLight(lights[i]);
  }

  Json::Value models = node["models"];
  for(int i=0;i<models.size();i++) {
    buildNode(models[i]);
  }

  Json::Value anims = node["animations"];
  for(int i=0;i<anims.size();i++) {
    buildAnimation(anims[i]);
  }

  mat4 wm = LookAt(eye, at, up);
  setWorldMatrix(LookAt(eye, at, up));
  printf("set init world matrix\n");
}

void Scene::mouseDragged(int dx, int dy) {
  float dPhi   = dx * pxToRad;
  float dTheta = dy * pxToRad;

  camTheta += dTheta;
  camPhi   += dPhi;

  recalculateCamera();

  mat4 mv = LookAt(eye, at, up);
  setWorldMatrix(mv);
}

void Scene::recalculateCamera() {
  //Ensure eye does not extend beyond [89,-89]
  float MAX_THETA = (89.0/360)*2*PI;
  if(camTheta > MAX_THETA) {
    camTheta = MAX_THETA;
  } else if(camTheta < -1*MAX_THETA) {
    camTheta = -1*MAX_THETA;
  }

  upTheta = camTheta + 90*degToRad;
  upPhi   = camPhi;

  eye = sphericalToPoint(camRadius, camTheta, camPhi, 1.);
  up  = sphericalToPoint(1, upTheta,  upPhi,  0.);
}

mat4 Scene::getView() {
  /*switch(camView) {
    case VIEW_PERSPECTIVE:
      return Perspective(fovy, aspect, zNear, zFar);
    case VIEW_ORTHOGRAPHIC:
      return Ortho(-1.5, 1.5, -1.5, 1.5, .5, 10.);
  }*/
  printf("getting perspective\n");
  return Perspective(fovy, aspect, zNear, zFar);
}

void Scene::setAspect(float aspect) {
  this->aspect = aspect;
  setProjection(getView());
}

void Scene::buildCamera(Json::Value camera) {
  printf("camera settings: %s\n",camera.toStyledString().c_str());
  fovy = camera["fovy"].asFloat();
  zNear = camera["zNear"].asFloat();
  zFar = camera["zFar"].asFloat();
  camTheta = camera["camTheta"].asFloat();
  camPhi = camera["camPhi"].asFloat();
  camRadius = camera["radius"].asFloat();
  eye = sphericalToPoint(1, camTheta, camPhi, 1.);
  at = (0., 0., 0., 1.);
  recalculateCamera();
  printVec("eye",eye);
  printVec("at",at);
  printVec("up",up);
  printf("built camera\n");
}

void Scene::buildNode(Json::Value node) {
  string type = node["type"].asString();

  if(type.compare("group") == 0) {
    buildGroup(node);
  } else if(type.compare("model") == 0) {
    models.push_back(buildModel(node));
  }

  /*if(node.isMember("children")) {
    Json::Value children = node["children"];
    for(int i=0; i<children.size(); i++) {
    buildNode(children[i]);
    }
    }*/
}

void Scene::buildLight(Json::Value light) {
  lights.push_back(new Light(
        getVec4(light["center"]),
        getVec4(light["ambient"]),
        getVec4(light["diffuse"]),
        getVec4(light["specular"]),
    getVec4(light.get("direction",light["center"])),
    light.get("angle",180).asFloat()));
}

void Scene::buildAnimation(Json::Value anim) {
  //printf("creating anim: %s\n",anim.toStyledString().c_str());
  string type = anim["type"].asString();

  //orbit
  if(type.compare("orbit") == 0) {
    Animation* animation = new OrbitalModel(
      (idModels.find(anim["center"].asString())->second),
      (idModels.find(anim["orbiter"].asString())->second),
      anim.get("distance","1").asFloat(),
      anim.get("theta","0").asFloat(),
      anim.get("phi","0").asFloat());
    animations.push_back(animation);
  }
  //oscillate
  else if(type.compare("oscillate") == 0) {
    vec3 max = getVec3(anim.get("max","[0,0,0]"));
	vec3 rate = getVec3(anim.get("rate","[0,0,0]"));
	vec3 center = getVec3(anim.get("center","[0,0,0]"));

    Animation* animation = new OscillatingModel(  
      (idModels.find(anim["object"].asString())->second),
	  max.x, max.y, max.z,
	  rate.x, rate.y, rate.z,
	  center.x, center.y, center.z );
	animations.push_back(animation);
	}
  else if(type.compare("controlled") == 0) {
	vec3 limit = getVec3(anim.get("limit","[0,0,0]"));

	Animation* animation = new ControlledModel(
      (idModels.find(anim["object"].asString())->second),
	  anim.get("speed",0.1).asFloat(),
	  limit.x, limit.y, limit.z );
	  animations.push_back(animation);
  }
}

Model* Scene::buildModel(Json::Value model) {
  string type = model["class"].asString();
  Model *retModel;

  // menger
  if(type.compare("Menger") == 0) {
    vec3 center = getVec3(model.get("center", "[0,0,0]"));
    printVec("center",center);
    float radius = model.get("radius", "1.0").asFloat();
    int subdivs = model.get("subdivisions", "2").asInt();
    retModel = new Menger(center, radius, subdivs);
  }
  // sphere
  else if(type.compare("Sphere") == 0) {
    Sphere *sphere;
    if(!model.isMember("ambient")) {
      sphere = new Sphere(
          model["radius"].asFloat(),
          model["subdivs"].asInt(),
          lights.size());
    } else {
      sphere = new Sphere(
          model["radius"].asFloat(),
          model["subdivs"].asInt(),
          lights.size(),
          getVec4(model.get("ambient","[1,0,1,1]")),
          getVec4(model.get("diffuse","[1,0.8,0,1]")),
          getVec4(model.get("specular","[1,0,1,1]")));
  }
    vector<Light*>::iterator it;
    int light = 0;
    for(it = lights.begin(); it != lights.end(); it++) {
      sphere->setLight((*it), light++);
    }
    retModel = sphere;
  } else if(type.compare("TexTri") == 0) {
    retModel = new TexTri(model["texture"].asString().c_str());
    printf("created textri\n");
  } else if(type.compare("ObjModel") == 0) {
    ObjModel *obj = new ObjModel(model["objfile"].asString().c_str(),
                            lights.size(),
                            getVec4(model.get("ambient","[1,1,1,1]")),
                            getVec4(model.get("diffuse","[1,1,1,1]")),
                            getVec4(model.get("specular","[1,1,1,1]")));
    vector<Light*>::iterator it;
    int light = 0;
    for(it = lights.begin(); it != lights.end(); it++) {
      obj->setLight((*it), light++);
  }
    retModel = obj;
  } else if(type.compare("Tesseract") == 0) {
    Tesseract *tess = new Tesseract( lights.size() );
    vector<Light*>::iterator it;
      int light = 0;
      for(it = lights.begin(); it != lights.end(); it++) {
    tess->setLight((*it), light++);
    }
    retModel = tess;
  }

  // map model if it has an id
  if(model.isMember("id")) {
    string id = model["id"].asString();
    nodes[id] = retModel;
    idModels[id] = retModel;
  }
  return retModel;
}

GroupNode* Scene::buildGroup(Json::Value groupDef) {
  GroupNode *group = new GroupNode();
  return group;
}

//{{{2 get functions
vec4 Scene::getVec4(Json::Value value) {
  return vec4(value[0].asFloat(), value[1].asFloat(), value[2].asFloat(),
      value[3].asFloat());
}

vec3 Scene::getVec3(Json::Value val) {
  return vec3(val[0].asFloat(), val[1].asFloat(), val[2].asFloat());
}

vec2 Scene::getVec2(Json::Value value) {
  return vec2(value[0].asFloat(), value[1].asFloat());
}

mat4 Scene::getMat4(Json::Value value) {
  return mat4(
      value[0][0].asFloat(), value[0][1].asFloat(), value[0][2].asFloat(), value[0][3].asFloat(),
      value[1][0].asFloat(), value[1][1].asFloat(), value[1][2].asFloat(), value[1][3].asFloat(),
      value[2][0].asFloat(), value[2][1].asFloat(), value[2][2].asFloat(), value[2][3].asFloat(),
      value[3][0].asFloat(), value[3][1].asFloat(), value[3][2].asFloat(), value[3][3].asFloat());
}

mat3 Scene::getMat3(Json::Value value) {
  return mat3(
      value[0][0].asFloat(), value[0][1].asFloat(), value[0][2].asFloat(),
      value[1][0].asFloat(), value[1][1].asFloat(), value[1][2].asFloat(),
      value[2][0].asFloat(), value[2][1].asFloat(), value[2][2].asFloat());
}
//}}}2
//}}}1
