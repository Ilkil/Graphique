void ViewerEtudiant::init_Cubemap()
{
    static Point pt[8] = { {-1,-1,-1}, {1,-1,-1}, {1,-1,1}, {-1,-1,1}, {-1,1,-1}, {1,1,-1}, {1,1,1}, {-1,1,1} };

    static int f[6][4] = { {0,1,2,3}, {5,4,7,6}, {2,1,5,6}, {0,3,7,4}, {3,2,6,7}, {1,0,4,5} };

    static Vector n[6] = { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };

    static vec2 tc[6][4] = {{{1/4.f,2/3.f},{1/4.f,1},{1/2.f,1},{1/2.f,2/3.f}},
                           {{1/4.f,0},{1/4.f,1/3.f},{1/2.f,1/3.f},{1/2.f,0}},
                           {{3/4.f,2/3.f},{1,2/3.f},{1,1/3.f},{3/4.f,1/3.f}},
                           {{1/4.f,2/3.f},{1/2.f,2/3.f},{1/2.f,1/3.f},{1/4.f,1/3.f}},
                           {{1/2.f,2/3.f},{3/4.f,2/3.f},{3/4.f,1/3.f},{1/2.f,1/3.f}},
                           {{0,2/3.f},{1/4.f,2/3.f},{1/4.f,1/3.f},{0,1/3.f}}
                           };
    
    int i;
    
    m_Cubemap=Mesh(GL_TRIANGLE_STRIP);
    m_Cubemap.color(Color(1,1,1));
    
    for (i=0;i<6;i++)
    {
        m_Cubemap.normal(n[i]);
        
        m_Cubemap.texcoord(tc[i][0],tc[i][0]);
        m_Cubemap.vertex(pt[f[i][0]]);
        
        m_Cubemap.texcoord(tc[i][1],tc[i][0]);
        m_Cubemap.vertex(pt[f[i][3]]);

        m_Cubemap.texcoord(tc[i][0],tc[i][1]);
        m_Cubemap.vertex(pt[f[i][1]]);
        
        m_Cubemap.texcoord(tc[i][1],tc[i][1]);
        m_Cubemap.vertex(pt[f[i][2]]);

        m_Cubemap.restart_strip();
    }
}