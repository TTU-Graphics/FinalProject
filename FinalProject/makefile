menger : main.cpp InitShader.cpp \
		model.o shadedModel.o instanceModel.o \
		menger.o colorTri.o sphere.o shadedTri.o texTri.o objModel.o tesseract.o \
		light.o \
		particles.o animation/particlesModel.o \
		helpers.o glslprogram.o \
		scene/scene.o scene/groupNode.o \
		libSOIL.a libjson.a \
		animation/orbitalModel.o animation/animator.o animation/animation.o \
		animation/oscillatingModel.o animation/controlledModel.o
	g++ -w \
		main.cpp InitShader.cpp \
		model.o shadedModel.o instanceModel.o \
		menger.o colorTri.o sphere.o shadedTri.o texTri.o objModel.o tesseract.o \
		light.o \
		particles.o animation/particlesModel.o \
		animation/orbitalModel.o animation/animator.o animation/animation.o \
		animation/oscillatingModel.o animation/controlledModel.o \
		helpers.o glslprogram.o \
		scene/scene.o scene/groupNode.o \
		libSOIL.a libjson.a \
		-o menger \
		-framework Carbon -framework OpenGL -framework GLUT \
		-framework CoreFoundation

#{{{ model types
model.o: model.h model.cpp abstractModel.h
	g++ -c model.cpp -o model.o

shadedModel.o: shadedModel.h shadedModel.cpp
	g++ -c shadedModel.cpp -o shadedModel.o

instanceModel.o: instanceModel.h instanceModel.cpp abstractModel.h
	g++ -c instanceModel.cpp -o instanceModel.o
#}}}
#{{{ models
menger.o: menger.h menger.cpp
	g++ -c menger.cpp -o menger.o

colorTri.o: colorTri.h colorTri.cpp
	g++ -c colorTri.cpp -o colorTri.o

shadedTri.o: shadedTri.h shadedTri.cpp
	g++ -c shadedTri.cpp -o shadedTri.o

sphere.o: sphere.h sphere.cpp
	g++ -c sphere.cpp -o sphere.o

texTri.o: texTri.h texTri.cpp
	g++ -c texTri.cpp -o texTri.o

objModel.o: objModel.h objModel.cpp
	g++ -c objModel.cpp -o objModel.o

tesseract.o: Tesseract.h Tesseract.cpp
	g++ -c Tesseract.cpp -o tesseract.o
#}}}
#{{{ lights
light.o: light.h light.cpp
	g++ -c light.cpp -o light.o
#}}}
#{{{ particles
particles.o: particles.h particles.cpp
	g++ -c particles.cpp -o particles.o

animation/particlesModel.o: animation/particlesModel.h animation/particlesModel.cpp
	g++ -c animation/particlesModel.cpp -o animation/particlesModel.o
#}}}
#{{{ animation
animation/animation.o: animation/animation.h animation/animation.cpp
	g++ -c animation/animation.cpp -o animation/animation.o

animation/orbitalModel.o: animation/orbitalModel.h animation/orbitalModel.cpp
	g++ -c animation/orbitalModel.cpp -o animation/orbitalModel.o

animation/animator.o: animation/animator.h animation/animator.cpp \
		animation/animation.o
	g++ -c animation/animator.cpp -o animation/animator.o

animation/oscillatingModel.o: animation/oscillatingModel.h animation/oscillatingModel.cpp
	g++ -c animation/oscillatingModel.cpp -o animation/oscillatingModel.o

animation/controlledModel: animation/controlledModel.h animation/controlledModel.cpp
	g++ -c animation/controlledModel.cpp -o animation/controlledModel.o
#}}}
#{{{ scene
scene/scene.o: scene/scene.h scene/scene.cpp
	g++ -c scene/scene.cpp -o scene/scene.o

scene/groupNode.o: scene/groupNode.h scene/groupNode.cpp
	g++ -c scene/groupNode.cpp -o scene/groupNode.o
#}}}
#{{{ misc
helpers.o: helpers.h helpers.cpp
	g++ -c helpers.cpp -o helpers.o

glslprogram.o: glslprogram.h glslprogram.cpp
	g++ -c glslprogram.cpp -o glslprogram.o
#}}}
