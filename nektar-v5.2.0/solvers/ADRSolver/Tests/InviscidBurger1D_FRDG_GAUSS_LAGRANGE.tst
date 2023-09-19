<?xml version="1.0" encoding="utf-8"?>
<test>
    <description>1D unsteady FRDG inviscidBurger GAUSS_LAGRANGE, P=10</description>
    <executable>ADRSolver</executable>
    <parameters>InviscidBurger1D_FRDG_GAUSS_LAGRANGE.xml</parameters>
    <files>
        <file description="Session File">InviscidBurger1D_FRDG_GAUSS_LAGRANGE.xml</file>
    </files>
    <metrics>
        <metric type="L2" id="1">
            <value variable="u" tolerance="1e-12">2.28218</value>
        </metric>
        <metric type="Linf" id="2">
            <value variable="u" tolerance="1e-12">2.48915</value>
        </metric>
    </metrics>
</test>
