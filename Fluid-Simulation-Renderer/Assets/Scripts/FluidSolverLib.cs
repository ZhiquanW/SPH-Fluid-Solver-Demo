using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Globalization;
using System.IO;

public class FluidDatabase {
    public float TimeStep { private get; set; }
    public float TimeDuration { private get; set; }
    public string FileName { get; set; }
    public List<List<Particle>> particle_database;

    public FluidDatabase() {
    }
}

public class Particle {
    public int index;
    public Vector3 position;
    public Particle(int inIndex) {
        index = inIndex;
    }
}