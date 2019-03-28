using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Serialization;

public class FluidManager : MonoBehaviour {
    public String fileName;
    public ParticleController particlePerfab;
    public int particleNum;
    public int fps;
    public int frameNum;
    public int currentFrame;
    public double frameInterval;
    public double animationDuration;
    public Color low_color;
    public Color high_color;
    public List<List<Vector3>> particleDatabase;
    public List<ParticleController> particleList;

    private void Awake() {
        LoadData();
    }

    // Start is called before the first frame update
    void Start() {
        for (int i = 0; i < particleNum; ++i) {
            var tmpObject = GameObject.Instantiate(particlePerfab);
            tmpObject.GetComponent<ParticleController>().index = i;
            tmpObject.transform.position = particleDatabase[0][i];
            particleList.Add(tmpObject);
        }
        SetParticleColor();
    }

    // Update is called once per frame
    void FixedUpdate() {
        if (currentFrame == frameNum - 1) {
            currentFrame = 0;
        }

        ++currentFrame;

        for (int i = 0; i < particleNum; ++i) {
            particleList[i].transform.position = particleDatabase[currentFrame][i];
        }
    }

    private void LoadData() {
        String[] lines;
        if (fileName == "test1") {
            lines = System.IO.File.ReadAllLines(
                @"/home/zhiquan/Git-Repository/Fluid-Solver-SPH/SampelCodes/cmake-build-debug/" + fileName);
        } else {
            lines = System.IO.File.ReadAllLines(
                @"/home/zhiquan/Git-Repository/Fluid-Solver-SPH/SPH-Fluid-Solver/cmake-build-debug/" + fileName);
        }


        string[] parameters = lines[1].Split(' ');
        particleNum = int.Parse(parameters[0]);
        frameNum = int.Parse(parameters[1]);
        frameInterval = Double.Parse(parameters[2]);
        animationDuration = Double.Parse(parameters[3]);
        fps = (int) (1 / frameInterval);


        particleDatabase = new List<List<Vector3>>();
        for (int i = 0; i < frameNum; ++i) {
            List<Vector3> tmp_list = new List<Vector3>();
            for (int j = 0; j < particleNum; ++j) {
                tmp_list.Add(new Vector3());
            }

            particleDatabase.Add(tmp_list);
        }

        for (int i = 0; i < frameNum; i++) {
            int startIndex = i * (particleNum + 1) + 3;
            int endIndex = startIndex + particleNum;
            for (int j = startIndex; j < endIndex; ++j) {
                var tmp_parameters = lines[j].Replace("(", "").Replace(")", "").Replace(",", " ").Split();
                var tmp_index = int.Parse(tmp_parameters[0]);
                var tmp_pos = new Vector3(float.Parse(tmp_parameters[1]), float.Parse(tmp_parameters[2]),
                    float.Parse(tmp_parameters[3]));
                particleDatabase[i][tmp_index] = tmp_pos;
            }
        }
    }

    private void SetParticleColor() {
        float max_height = -float.MaxValue;
        float min_height = float.MaxValue;
        foreach (var p in particleList) {
            if (p.transform.position.y > max_height) {
                max_height = p.transform.position.y;
            }

            if (p.transform.position.y < min_height) {
                min_height = p.transform.position.y;
            }
        }
        Debug.Log(min_height);
        Debug.Log(max_height);

        Color offset_color = high_color - low_color;
        float offset_height = max_height - min_height;
        foreach (var p in particleList) {
            float rate = (p.transform.position.y - min_height) / offset_height;
            p.GetComponent<MeshRenderer>().material.color = low_color + rate *offset_color ;
        }
    }
}