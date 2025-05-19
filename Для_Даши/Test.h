#pragma once
void add_test_objects(SpaseAtlas* atl) {
    //�������
    // ������
    push_Back(atl, OBJ_STAR, createOfStar(
        L"������",
        8.6,
        -1.46,
        L"A1V",
        -16.7161,
        {
        6, 45, 8.9
        },
        2.02
    ));

    // �����������
    push_Back(atl, OBJ_STAR, createOfStar(
        L"�����������",
        640.0,
        0.5,
        L"M1-2Ia",
        7.4072,
        {
        5, 55, 10.3
        },
        11.6
    ));

    // ����
    push_Back(atl, OBJ_STAR, createOfStar(
        L"����",
        25.04,
        0.03,
        L"A0Va",
        38.7836,
        {
        18, 36, 56.3
        },
        2.135
    ));

    // ����������
    push_Back(atl, OBJ_STAR, createOfStar(
        L"����������",
        65.3,
        0.85,
        L"K5III",
        16.5095,
        {
        4, 35, 55.2
        },
        1.16
    ));

    // ������
    push_Back(atl, OBJ_STAR, createOfStar(
        L"������",
        860.0,
        0.12,
        L"B8Ia",
        -8.2016,
        {
        5, 14, 32.3
        },
        21.0
    ));

    // ר���� ����
    push_Back(atl, OBJ_BLACKHOLE, createOfBlackHole(
        L"������� A*",
        26000.0,
        L"��������������",
        -29.0078,
        {
        17, 45, 40.04
    },
        4.154e6
    ));

    push_Back(atl, OBJ_BLACKHOLE, createOfBlackHole(
        L"������ X-1",
        6070.0,
        L"�������",
        35.2016,
        {
        19, 58, 21.68
    },
        14.8
    ));

    // ����������
    push_Back(atl, OBJ_NEBULA, createOfNebula(
        L"������",
        1344.0,
        L"�����������",
        -5.23,
        {
        5, 35, 17.3
    },
        2000.0
    ));

    push_Back(atl, OBJ_NEBULA, createOfNebula(
        L"������",
        655.0,
        L"�����������",
        -20.8447,
        {
        22, 29, 38.55
    },
        0.89
    ));

    // ��������
    push_Back(atl, OBJ_PULSAR, createOfPulsar(
        L"PSR B0531+21",
        6500.0,
        22.0144,
        {
        5, 34, 31.97
    },
        1.4,
        30.2,
        16.5
    ));

    push_Back(atl, OBJ_PULSAR, createOfPulsar(
        L"PSR J1748-2446",
        18000.0,
        -24.7839,
        {
        17, 48, 04.9
    },
        2.0,
        716.0,
        21.3
    ));

    // ���������
    push_Back(atl, OBJ_GALAXY, createOfGalaxy(
        L"���������",
        2537.0,
        41.2692,
        {
        0, 42, 44.3
    },
        1.5e12,
        1e12
    ));

    push_Back(atl, OBJ_GALAXY, createOfGalaxy(
        L"��������",
        29.35,
        -11.6234,
        {
        12, 39, 59.4
    },
        8e11,
        1e11
    ));

    // �¨����� ���������
    push_Back(atl, OBJ_STARCLASTER, createOfStarCluster(
        L"������",
        444.0,
        24.1167,
        {
        3, 47, 24.0
    },
        800.0,
        1000
    ));

    push_Back(atl, OBJ_STARCLASTER, createOfStarCluster(
        L"����",
        577.0,
        19.8325,
        {
        8, 40, 24.0
    },
        350.0,
        1000
    ));
}
