/*select $**/

/*out_name = ((GetDir #export) + "/" + "body.am")*/
out_name = getsavefilename caption:"Export to..." types:"Data(*.am)|*.am"
out_file = createfile out_name

format "SimpleMeshFormat 1\n" to:out_file

format "%\n" selection.count to:out_file

for obj in $ do
(
	
	actualMesh = snapshotAsMesh obj as TriMesh

	format "%\n" obj.name to:out_file
	
	numVerts = actualMesh.numverts
	numFaces = actualMesh.numfaces

	format "%\n" numVerts to:out_file	
	
	for v = 1 to numVerts do
	(
		vert = getVert actualMesh v
		format "% % %\n" vert.x vert.y vert.z to:out_file
	)		
	
	if actualMesh.numtverts > 0 then
	(
	    format "%\n" numVerts to:out_file	
	
	    for v = 1 to numVerts do
	    (
		    vertUV = getTVert actualMesh v
			format "% %\n" vertUV.x vertUV.y to:out_file
	    )
    )
    else
    (
			format "0\n" to:out_file	
    )		
	
	
	format "%\n" numFaces to:out_file

	for f=1 to numFaces do
	(
		smoothgroup = getFaceSmoothGroup actualMesh f
	
		face = getFace actualMesh f
		
		xi = face.x as integer
		yi = face.y as integer
		zi = face.z as integer		
	
		/* index start from 0 */
		xi = xi - 1
		yi = yi - 1
		zi = zi - 1
		
		normal_v1 = getNormal actualMesh face.x
		normal_v2 = getNormal actualMesh face.y
		normal_v3 = getNormal actualMesh face.z
		
		-- Get 3 face tex verts
/*	
		texVert1   = getTVert actualMesh face.x
		texVert1.y = (1 - texVert1.y)
		
		texVert2   = getTVert actualMesh face.y
		texVert2.y = (1 - texVert2.y)
		
		texVert3   = getTVert actualMesh face.z
		texVert3.y = (1 - texVert3.y)		
*/

		
/*	
		mapFace = meshop.getMapFace actualMesh 1 f
		
		uvw1 = meshop.getMapVert actualMesh 1 mapFace.x  
		uvw1_x = uvw1.x
		uvw1_y = (0 - (uvw1.y - 1))
		--uvw1_y = uvw1.y
		uvw2 = meshop.getMapVert actualMesh 1 mapFace.y		
		uvw2_x = uvw2.x
		uvw2_y = (0 - (uvw2.y - 1))			
		--uvw2_y = uvw2.y
		uvw3 = meshop.getMapVert actualMesh 1 mapFace.z		
		uvw3_x = uvw3.x
		uvw3_y = (0 - (uvw3.y - 1))
		--uvw3_y = uvw3.y		
*/	
		--format "% % % % % % % % % % % % % % % % % % %\n" smoothgroup xi yi zi normal_v1.x normal_v1.y normal_v1.z normal_v2.x normal_v2.y normal_v2.z normal_v3.x normal_v3.y normal_v3.z texVert1.x texVert2.x  texVert3.x texVert1.y  texVert2.y texVert3.y to:out_file
		--format "% % % % % % % % % % % % % % % % % % %\n" smoothgroup xi yi zi normal_v1.x normal_v1.y normal_v1.z normal_v2.x normal_v2.y normal_v2.z normal_v3.x normal_v3.y normal_v3.z uvw1.x uvw2.x  uvw3.x uvw1.y  uvw2.y uvw3.y to:out_file
		format "% % % % % % % % % % % % % 0 0 0 0 0 0\n" smoothgroup xi yi zi normal_v1.x normal_v1.y normal_v1.z normal_v2.x normal_v2.y normal_v2.z normal_v3.x normal_v3.y normal_v3.z to:out_file		
	)		
	

	
	
	midold = -1
	objMaterials = #()
	
	for f = 1 to numFaces do	
	(
		face = getFace actualMesh f
		materialClass = classof obj.material
		
		if(materialClass == Standardmaterial) then
		(
			matname = obj.material
			objMaterial = obj.material
		   	
			if (findItem objMaterials objMaterial == 0) then
			(
				append objMaterials objMaterial
			)			
			
		)
		else if (materialClass != UndefinedClass) then
		(
			matid = getFaceMatId actualMesh f
			matname = obj.material[matid]
			objMaterial = obj.material[matid]
			
			if (findItem objMaterials objMaterial == 0) then
			(
				append objMaterials objMaterial
			)
			
		)
		
	)
	
	format "%\n" objMaterials.count to:out_file
	
	for objm in objMaterials do
	(
		/*format "%\n" objm to:out_file*/
		ambient_r = objm.ambient.r / 255
		ambient_g = objm.ambient.g / 255
		ambient_b = objm.ambient.b / 255		
		diffuse_r = objm.diffuse.r / 255
		diffuse_g = objm.diffuse.g / 255
		diffuse_b = objm.diffuse.b / 255		
		specular_r = objm.specular.r / 255
		specular_g = objm.specular.g / 255
		specular_b = objm.specular.b	/ 255	
		self_illum_r = objm.selfIllumColor.r/255
		self_illum_g = objm.selfIllumColor.g/255
		self_illum_b = objm.selfIllumColor.b/255		
		specular_level = objm.specularLevel		
		glossiness = objm.Glossiness
		
		format "% % % % % % % % % % % % % %\n" specular_level glossiness ambient_r ambient_g ambient_b diffuse_r diffuse_g diffuse_b specular_r specular_g specular_b self_illum_r self_illum_g self_illum_b to:out_file
		/*format "% % % % % % % % %\n" objm.ambient.r objm.ambient.g objm.ambient.b objm.diffuse.r objm.diffuse.g objm.diffuse.b objm.specular.r objm.specular.g objm.specular.b to:out_file		*/
	)
	
)

close out_file

