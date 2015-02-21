
#include "main.h"


unsigned int test0(unsigned int size) {
	std::vector<std::vector<unsigned int>> faces(size, std::vector<unsigned int>(3));
	for (unsigned int i = 0; i < faces.size(); i++) {
		faces[i][0] = i*3+0;
		faces[i][1] = i*3+1;
		faces[i][2] = i*3+2;
	}
	unsigned int sum = 0;
	for (unsigned int i = 0; i < faces.size(); i++) {
		sum += faces[i][0];
		sum += faces[i][1];
		sum += faces[i][2];
	}
	return sum;
}

unsigned int test1(unsigned int size) {
	std::vector<unsigned int> faces(size*3);
	for (unsigned int i = 0; i < size; i++) {
		faces[3*i+0] = i*3+0;
		faces[3*i+1] = i*3+1;
		faces[3*i+2] = i*3+2;
	}
	unsigned int sum = 0;
	for (unsigned int i = 0; i < size; i++) {
		sum += faces[3*i+0];
		sum += faces[3*i+1];
		sum += faces[3*i+2];
	}
	return sum;
}

unsigned int test2(unsigned int size) {
	MeshDataf::Indices faces;
	faces.reserve(size);
	for (unsigned int i = 0; i < size; i++) {
		unsigned int curr[] = {i*3+0, i*3+1, i*3+2};
		faces.addFace(curr, 3);
		//faces[3*i+0] = i*3+0;
		//faces[3*i+1] = i*3+1;
		//faces[3*i+2] = i*3+2;
	}
	unsigned int sum = 0;
	for (unsigned int i = 0; i < size; i++) {
		auto f = faces.getFace(i);
		sum += f[0];
		sum += f[1];
		sum += f[2];
		//sum += faces[3*i+0];
		//sum += faces[3*i+1];
		//sum += faces[3*i+2];
	}
	return sum;
}

//unsigned int test3(unsigned int size) {
//	MeshDataf::Indices0 faces;
//	faces.reserve(size);
//	for (unsigned int i = 0; i < size; i++) {
//		unsigned int curr[] = {i*3+0, i*3+1, i*3+2};
//		faces.addFace(curr, 3);
//		//faces[3*i+0] = i*3+0;
//		//faces[3*i+1] = i*3+1;
//		//faces[3*i+2] = i*3+2;
//	}
//	unsigned int sum = 0;
//	for (unsigned int i = 0; i < size; i++) {
//		auto f = faces.getFace(i);
//		sum += f[0];
//		sum += f[1];
//		sum += f[2];
//		//sum += faces[3*i+0];
//		//sum += faces[3*i+1];
//		//sum += faces[3*i+2];
//	}
//	return sum;
//}

void testCollisions() {
	BoundingBox3f bb0(vec3f(0,0,0), vec3f(1,1,1));
	BoundingBox3f bb1(vec3f(-1,-1,-1), vec3f(-0.5f,0.5f,0.5f));
	for (unsigned int i = 0; i < 10000; i++) {
		bb1.translate(vec3f(0.001f, 0.001f, 0.001f));
		if (bb0.intersects(bb1)) {
			std::cout << i << std::endl;
			std::cout << bb1 << std::endl;
			break;
		}
	}

	{
		Timer cTime;
		TriMeshf s0 = shapes::sphere(0.5f, vec3f(-2.0f + 1300*0.002f), 50, 50);
		TriMeshf s1 = shapes::sphere(0.5f, vec3f(1.0f), 15, 15);
		TriMeshAcceleratorBVHf accels0(s0);
		TriMeshAcceleratorBVHf accels1(s1);
		unsigned int numCols = 0;
		for (unsigned int i = 0; i < 10000; i++) {
			if (accels0.collision(accels1)) {
				numCols++;
			}
		}
		std::cout << "bvh collision time:\t" << cTime.getElapsedTimeMS() << " ms | " << numCols << std::endl;
	}

	Timer tbvh;
	for (unsigned int i = 0; i < 10000; i++) {
		TriMeshf s0 = shapes::sphere(0.5f, vec3f(-2.0f + i*0.002f), 50, 50);
		TriMeshf s1 = shapes::sphere(0.5f, vec3f(1.0f), 15, 15);
		TriMeshAcceleratorBVHf accels0(s0);
		TriMeshAcceleratorBVHf accels1(s1);
		//std::cout << i << std::endl;
		if (accels0.collision(accels1)) {
			std::cout << "BVH:\t" << i << std::endl;
			break;
		}
	}
	std::cout << "tbvh:\t" << tbvh.getElapsedTimeMS() << std::endl; 
	
	Timer tbrute;
	for (unsigned int i = 0; i < 10000; i++) {
		TriMeshf s0 = shapes::sphere(0.5f, vec3f(-2.0f + i*0.002f), 50, 50);
		TriMeshf s1 = shapes::sphere(0.5f, vec3f(1.0f), 15, 15);
		TriMeshAcceleratorBruteForcef accels0(s0);
		TriMeshAcceleratorBruteForcef accels1(s1);
		//std::cout << i << std::endl;
		if (accels0.collision(accels1)) {
			std::cout << "BruteForce:\t" << i << std::endl;
			break;
		}
	}
	std::cout << "tbrute:\t" << tbrute.getElapsedTimeMS() << std::endl; 
}

void AppTest::init(ml::ApplicationData &app)
{
	//testCollisions();


	//TriMeshf s = shapes::sphere(0.1f, vec3f(0.0f), 50, 50);
	//MeshIOf::saveToFile("bla0.ply",s.getMeshData());
	//OpenMeshTriMesh::Mesh omesh;
	//OpenMeshTriMesh::convertToOpenMesh(s, omesh);
	//OpenMeshTriMesh::convertToTriMesh(omesh, s);
	//MeshIOf::saveToFile("bla1.ply",s.getMeshData());
	////MeshDataf meshData0 = s.getMeshData();
	////meshData0.mergeCloseVertices(0.00001f, true);
	////s = TriMeshf(meshData0);
	//MeshIOf::saveToFile("bla2.ply",s.getMeshData());
	//OpenMeshTriMesh::decimate(s, 500);
	//MeshIOf::saveToFile("bla3.ply",s.getMeshData());

	////vec3f u0(0,0,0);
	////vec3f u1(0,1,0);
	////vec3f u2(0,1,1);
	////vec3f v0(-0.25,0.25,0.25);
	////vec3f v1(1,1,0);
	////vec3f v2(1,1,1);

	//vec2f t0(0,0);
	//vec3f t1(t0, 0.0f);

	//vec3f u0(0,0,0);
	//vec3f u1(0,1,0);
	//vec3f u2(0,1,1);
	//vec3f v0(0,0,0);
	//vec3f v1(0,0,1);
	//vec3f v2(0,1,0);

	//bool b0 = intersection::intersectTriangleTriangle(u0,u1,u2, v0,v1,v2);
	//
	//std::cout << (int)b0 << std::endl;


	//DenseMatrixf md(3);
	//for (unsigned int i = 0; i < 9; i++) {
	//	md[i] = (float)i;
	//}
	////std::cout << md.rank() << std::endl << std::endl;

	//mat2f m2;
	//for (unsigned int i = 0; i < 4; i++) {
	//	m2[i] = (float)i;
	//}
	////std::cout << m2.rank() << std::endl << std::endl;
	//mat4f m4;
	//for (unsigned int i = 0; i < 16; i++) {
	//	m4[i] = (float)i;
	//}
	////std::cout << m4.rank() << std::endl << std::endl;
	//mat3f m3;	
	//for (unsigned int i = 0; i < 9; i++) {
	//	m3[i] = (float)i;
	//}
	////std::cout << m3.rank() << std::endl;
	////m.setDiag(1.0f, 2.0f, 3.0f);

	//EigenSystemf esd_VTK = EigenSolverf::solve<EigenSolverf::TYPE_NR>(md);
	//EigenSystemf esd_NR = EigenSolverf::solve<EigenSolverf::TYPE_VTK>(md);

	////std::cout << esd_VTK << std::endl;
	////std::cout << esd_NR << std::endl;

	////EigenSystemf esd = md.eigenSystem();
	////EigenSystemf es4 = m4.eigenSystem();
	////EigenSystemf es3 = m3.eigenSystem();
	////EigenSystemf es2 = m2.eigenSystem();

	////std::cout << esd << std::endl;
	////std::cout << es4 << std::endl;
	////std::cout << es3 << std::endl;
	////std::cout << es2 << std::endl;


	////std::cout << m3 << std::endl << std::endl;


	//MeshDataf::Indices indices;
	////for (auto i = indices.begin(); i != indices.end(); i++) {}
	////for (auto face : indices) {}
	////for (auto face: indices) {}


	////unsigned int size = 50000;
	////Timer t;
	////std::cout << test0(size) << std::endl;
	////std::cout << t.getElapsedTimeMS() << std::endl;
	////t.start();
	////std::cout << test1(size) << std::endl;
	////std::cout << t.getElapsedTimeMS() << std::endl;
	////t.start();
	////std::cout << test2(size) << std::endl;
	////std::cout << t.getElapsedTimeMS() << std::endl;

	////PointCloudf pc = PointCloudIOf::loadFromFile("bunny.ply");

	////int a = 5;

	////vec3f testVec(1.0f, 2.0f, 3.0f);
	////float* f = testVec.ptr();

	////unsigned int numSamples = 10000;
	////std::vector<vec3f> res_uniformSphere(numSamples);
	////std::vector<vec3f> res_uniformHemisphere(numSamples);
	////std::vector<vec3f> res_cosineHemisphere(numSamples);
	////std::vector<vec3f> res_powerCosineSampleHemisphere(numSamples);
	////RNG r;
	////for (unsigned int i = 0; i < numSamples; i++) {
	////	res_uniformSphere[i] = Samplef::squareToUniformSphere(r.uniform2D());
	////	res_uniformHemisphere[i] = Samplef::squareToUniformHemisphere(r.uniform2D());
	////	res_cosineHemisphere[i] = mat3f::frame(vec3f(0, 0, -1))*Samplef::squareToCosineHemisphere(r.uniform2D());
	////	res_powerCosineSampleHemisphere[i] = Samplef::squareToPowerCosineSampleHemisphere(r.uniform2D(), 100000);
	////}
	////PointCloudIOf::saveToFile("sample_uniformSphere.ply", res_uniformSphere);
	////PointCloudIOf::saveToFile("sample_uniformHemisphere.ply", res_uniformHemisphere);
	////PointCloudIOf::saveToFile("sample_cosineHemisphere.ply", res_cosineHemisphere);
	////PointCloudIOf::saveToFile("sample_powerCosineSampleHemisphere.ply", res_powerCosineSampleHemisphere);

 //   //const std::string testPLY = "scans/gates381.ply";
 //   //const TriMesh triMesh = OpenMeshLoader::load(testPLY);
 //   //m_mesh.load(app.graphics, triMesh);

	////const std::string testFilename = "scans/gates381.off";
	////const std::string testFilename = "scans/gates381.obj";
	//const std::string testFilename = "scans/gates381.ply";
	////const std::string testFilename = "scans/gates381_ascii.ply";
	//ml::MeshDataf meshData = ml::MeshIOf::loadFromFile(testFilename);
	////ml::MeshDataf bunny = MeshIOf::loadFromFile("bunny_color.ply");

	////bunny.m_Colors.resize(bunny.m_Vertices.size(), vec4f(0.5f, 0.5f, 0.5f, 1.0f));
	////meshData.merge(bunny);
	////meshData.m_Vertices.push_back(vec3f(1.0f, 2.0f, 3.0f));
	////meshData.m_Colors.push_back(vec4f(1.0f, 0.0f, 0.0f, 1.0f));
	////meshData.m_Normals.push_back(vec3f(1.0f, 0.0f, 0.0f));
	////std::cout << meshData.m_Vertices.size();
	////std::cout << " reduced to " << meshData.removeIsolatedVertices() << std::endl;
	////std::cout << meshData.m_Vertices.size();
	////std::cout << " reduced to " << meshData.removeFacesInFrontOfPlane(Planef::xyPlane(), 0.1f) << std::endl;
	// 
	//assert(meshData.isConsistent());

	////for (size_t i = 0; i < meshData.m_Colors.size(); i++) {
	////	meshData.m_Colors[i] = ml::vec4f(1.0f, 0.0f, 0.0f, 1.0f);
	////}
	////ml::MeshIOf::saveToFile("outtest.ply", meshData);
	////ml::MeshIOf::saveToFile("outtest.off", meshData);
	////ml::MeshIOf::saveToFile("outtest.obj", meshData);

	////meshData.clear();
	////MeshIOf::loadFromFile("outtest.obj", meshData);

	////meshData.mergeCloseVertices(0.3f, false);
	////meshData.mergeCloseVertices(pow(0.3f,3), true);
	//
	////MeshDataf copy = meshData;
	////copy.applyTransform(mat4f::translation(vec3f(-2,1,1)));
	////meshData.merge(copy);
	//MeshDataf bbData = shapes::toMeshData(meshData.getBoundingBox(), vec4f(1,1,1,1), true);
	//bbData.subdivideFacesMidpoint();
	//bbData.subdivideFacesLoop();
	////bbData.print();
	//MeshIOf::saveToFile("outbox.ply", bbData);
	//meshData.merge(bbData);
	//assert(meshData.isConsistent());


	//meshData.clear();
	//MeshIOf::loadFromFile("1a8e293609eca3b3f7e27638e63d848.obj", meshData);
	//auto materialMeshes = meshData.splitByMaterial();
	//std::vector<Materialf> mats;
	//Materialf::loadFromMTL("out.mtl", mats);

  MeshDataf meshData = MeshIOf::loadFromFile("scans/gates381.ply");
	ml::TriMeshf triMesh(meshData);
	//triMesh.setColor(vec4f(0.0f, 1.0f, 0.0f, 1.0f));
	//auto p = meshData.getBoundingBox().getBottomPlane();


	//const ml::TriMesh triMesh(meshData);
	std::vector<ml::TriMeshf> meshes;
	//m_mesh.load(app.graphics, triMesh);
	//{
	//	meshes.push_back(ml::TriMeshf(triMesh.getBoundingBox()));
	//}
	meshes.push_back(triMesh);
	//for (auto& m : materialMeshes) {
	//	meshes.push_back(TriMeshf(m.first));
	//	meshes.back().setColor(vec4f(1.0f, 1.0f, 0.0f, 1.0f));
	//}
	m_mesh.load(app.graphics, ml::TriMeshf(ml::meshutil::createUnifiedMesh(meshes)));
	//std::vector<ml::vec4f> color(meshData.m_Vertices.size(), ml::vec4f(1.0f, 0.0f, 0.0f, 1.0f));
	//m_mesh.updateAttributeA(app.graphics, color);

	auto lambdaPoints = [=] (ml::vec3f& v) { v = ml::vec3f(-2.f*(float)rand() / RAND_MAX, -2.f*(float)rand() / RAND_MAX, (float)rand() / RAND_MAX);};
	std::vector<ml::vec3f> points(5000);
	std::for_each(points.begin(), points.end(), lambdaPoints);

    m_pointCloud.load(app.graphics, ml::meshutil::createPointCloudTemplate(ml::shapes::box(0.01f), points));

    m_vsColor.load(app.graphics, "shaders/test.shader");
    m_psColor.load(app.graphics, "shaders/test.shader");

    m_vsPointCloud.load(app.graphics, "shaders/pointCloud.shader");
    m_psPointCloud.load(app.graphics, "shaders/pointCloud.shader");

    m_constants.init(app.graphics);

    //vec3f eye(1.0f, 2.0f, 3.0f);
    ml::vec3f eye(-0.5f, -0.5f, 1.5f);
    ml::vec3f worldUp(0.0f, 0.0f, 1.0f);
    m_camera = ml::Cameraf(eye, worldUp, ml::vec3f::eX, 60.0f, (float)app.window.width() / app.window.height(), 0.01f, 1000.0f);

    m_font.init(app.graphics, "Calibri");


	m_canvas.init(app.graphics);
	m_canvas.addCircle(vec2f(500, 500), 50, RGBColor::Green, 0.5f);
}

void AppTest::render(ml::ApplicationData &app)
{
    m_timer.frame();

	m_canvas.render();

    mat4f model = mat4f::translation(0, 2, 0);
    ConstantBuffer constants;
    constants.worldViewProj = m_camera.cameraPerspective() * model;
    m_constants.update(constants);

    m_vsColor.bind();
    m_psColor.bind();
    m_constants.bindVertexShader(0);

    m_mesh.render();

    m_vsPointCloud.bind();
    m_psPointCloud.bind();
    m_constants.bindVertexShader(0);

    m_pointCloud.render();

    m_font.drawString(app.graphics, "FPS: " + ml::convert::toString(m_timer.framesPerSecond()), ml::vec2i(10, 5), 24.0f, ml::RGBColor::Red);
}

void AppTest::resize(ml::ApplicationData &app)
{
    m_camera.updateAspectRatio((float)app.window.width() / app.window.height());
	
}

void AppTest::keyDown(ml::ApplicationData &app, UINT key)
{

}

void AppTest::keyPressed(ml::ApplicationData &app, UINT key)
{
    const float distance = 0.1f;
    const float theta = 5.0f;

    if(key == KEY_S) m_camera.move(-distance);
    if(key == KEY_W) m_camera.move(distance);
    if(key == KEY_A) m_camera.strafe(-distance);
    if(key == KEY_D) m_camera.strafe(distance);
	if(key == KEY_E) m_camera.jump(distance);
	if(key == KEY_Q) m_camera.jump(-distance);

    if(key == KEY_UP) m_camera.lookUp(theta);
    if(key == KEY_DOWN) m_camera.lookUp(-theta);
    if(key == KEY_LEFT) m_camera.lookRight(theta);
    if(key == KEY_RIGHT) m_camera.lookRight(-theta);

	if(key == 'R') {
		float fovX = m_camera.getFoV();
		float fovY = fovX/m_camera.getAspect();
		float focalLengthX = 0.5f * (float)app.window.width() / tan(0.5f * math::degreesToRadians(fovX));
		float focalLengthY = 0.5f * (float)app.window.height() / tan(0.5f * math::degreesToRadians(fovY));
		mat4f intrinsics = 
			ml::mat4f(
			focalLengthX, 0.0f, (float)app.window.width()/2.f, 0.0f,
			0.0f, focalLengthY, (float)app.window.height()/2.f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
		mat4f intrinsicsInverse = intrinsics.getInverse();

		ml::mat4f projToCam = m_camera.perspective().getInverse();
		ml::mat4f camToWorld = m_camera.camera().getInverse();
		ml::mat4f trans =  camToWorld * projToCam;
		ml::ColorImageRGB image(app.window.height(), app.window.width());

		const std::string testFilename = "scans/gates381.ply";
		ml::MeshDataf meshData = ml::MeshIOf::loadFromFile(testFilename);
		ml::TriMeshf triMesh(meshData);

		//std::cout << triMesh.getBoundingBox() << std::endl;

		ml::Timer c0;
		c0.start(); 
		ml::TriMeshAcceleratorBVHf accel(triMesh, false);
		//ml::TriMeshAcceleratorBruteForcef accel(triMesh);
		std::cout << "time construct " << c0.getElapsedTimeMS() << std::endl;

		std::vector<const TriMeshRayAcceleratorf*> accelVec;
		accelVec.push_back(&accel);
		int s = sizeof(accel);

		ml::Timer c;
		c.start();
#pragma omp parallel for
		for (int i_ = 0; i_ < (int)app.window.height(); i_++) {
			unsigned int i = (unsigned int)i_;
			for (unsigned int j = 0; j < app.window.width(); j++) {
				//std::cout << " tyring ray " << i << " " << j << std::endl;

				float depth0 = 0.5f;
				float depth1 = 1.0f;
				vec4f p0 = camToWorld*intrinsicsInverse*vec4f((float)(app.window.width()-1-j)*depth0, (float)i*depth0, depth0, 1.0f);
				vec4f p1 = camToWorld*intrinsicsInverse*vec4f((float)(app.window.width()-1-j)*depth1, (float)i*depth1, depth1, 1.0f);

				vec3f eye = m_camera.getEye();
				Rayf r(m_camera.getEye(), (p0.getVec3() - p1.getVec3()).getNormalized());

				mat4f tmp = mat4f::rotationZ(45.0f);
				r = tmp * r;

				//ml::vec4f p((float)j, (float)i, 0.5f, 1.0f);
				//p.x /= app.window.width();
				//p.y /= app.window.height();
				//p.x = 2.0f*p.x - 1.0f;
				//p.y = 1.0f-2.0f*p.y;
				//p = trans * p;
				//p /= p.w;
				//Rayf r1(m_camera.getEye(), (ml::vec3f(p.x,p.y,p.z)-m_camera.getEye()).getNormalized());

				float t,u,v;	
				//const ml::TriMeshf::Trianglef* tri = accel.intersect(r, t, u, v);
				const ml::TriMeshf::Trianglef* tri;
				unsigned int objIdx;
				TriMeshRayAcceleratorf::Intersection intersect = TriMeshRayAcceleratorf::getFirstIntersection(r, accelVec, objIdx);
				t = intersect.t;
				u = intersect.u;
				v = intersect.v;
				tri = intersect.triangle;

				if (tri) {
					image(i,j) = tri->getSurfaceColor(u,v).getVec3();
				} else {
					image(i,j) = 0;
				}
			
			}
		}
		double elapsed = c.getElapsedTimeMS();
		std::cout << "time trace " << elapsed << std::endl;
		unsigned int raysPerSec = (unsigned int)((double)(app.window.height()*app.window.width())/(elapsed/1000.0));
		std::cout << "million rays/s " << (float)raysPerSec/1000000.0 << std::endl;

		ml::FreeImageWrapper::saveImage("test.jpg", image);

	}
}

void AppTest::mouseDown(ml::ApplicationData &app, ml::MouseButtonType button)
{

}

void AppTest::mouseWheel(ml::ApplicationData &app, int wheelDelta)
{
    const float distance = 0.002f;
    m_camera.move(distance * wheelDelta);
}

void AppTest::mouseMove(ml::ApplicationData &app)
{
    const float distance = 0.01f;
    const float theta = 0.5f;

    ml::vec2i posDelta = app.input.mouse.pos - app.input.prevMouse.pos;

    if(app.input.mouse.buttons[ml::MouseButtonRight])
    {
        m_camera.strafe(-distance * posDelta.x);
        m_camera.jump(distance * posDelta.y);
    }

    if(app.input.mouse.buttons[ml::MouseButtonLeft])
    {
        m_camera.lookRight(-theta * posDelta.x);
        m_camera.lookUp(theta * posDelta.y);
    }

}
