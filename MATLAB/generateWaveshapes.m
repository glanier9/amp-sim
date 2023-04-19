%% Retrofuturistic Hardware VIP - Amp Sim - Generate Waveshapes
% Generates waveshape graphs for images. Processes a voltage input vector 
% to get a voltage output vector based on the function.

% How To Use
% Matlab dark mode requres a medium for a dark background. There is no
% quick way to save the image without mismatching some colors. The
% PowerPoint slides provided can be used. Run the setup code at the
% beginning (first section), then either run all at once or run by section
% to generate the figures. Afterwards, in the figure windo, click Edit >
% Copy Figure. Pase this coppied figure into a PowerPoint slide (image size
% should match the slide exactly). To match pixel size on the ppt, click 
% Design > Slize Size, and use px to signify pixels (ex. 229px). When done,
% click File > Export, select the File Format: PNG and Save Current Slide 
% Only. Save this to the WaveshaperImage directory in the AmpSim repo. Open
% up ProJucer. Right click the folder Resources > WaveshaperImages and
% click Add Existing Files. Add all newly saved images. Make appropriate
% changes in the code.

%% General Settings
% Used across different sections to process the functions

% Setup
imageSize = 229;                % Size of width/height in pixels
v_in = linspace(-1, 1, 100);    % Voltage input vector for functions
v_out = zeros(1, length(v_in)); % Voltage output vector for functions

%% Squeakky Clean: y = x

% Process voltage vector
for x = 1 : length(v_in)
    v_out(x) = v_in(x);
end

% Generate figure
figure
    xlim([-1 1])
    ylim([-1 1])
    xlabel("Voltage In");
    ylabel("Voltage Out");
    % set(gca,'Visible','off');
    set(gcf,'position',[0,0,imageSize,imageSize])
    % set(gcf,'color','k');
    hold on;
        yline(0, 'w'); xline(0, 'w');   % Axis lines
        plot(v_in, v_out, 'y');         % Waveshaping funciton
    hold off;
    plot_darkmode;

%% Asinine: y = x/(abs(x) + 1)

% Process voltage vector
for x = 1 : length(v_in)
    v_out(x) = v_in(x)/(abs(v_in(x)) + 1);
end

% Generate figure
figure
    xlim([-1 1])
    ylim([-1 1])
    xlabel("Voltage In");
    ylabel("Voltage Out");
    set(gcf,'position',[0,0,imageSize,imageSize])
    hold on;
        yline(0, 'w'); xline(0, 'w');  
        plot(v_in, v_out, 'b');        
    hold off;
    plot_darkmode;

%% Reptile: y = (2/pi)*arctan(x * pi/2)

% Process voltage vector
for x = 1 : length(v_in)
    v_out(x) = (2/pi)*atan(v_in(x) * pi/2);
end

% Generate figure
figure
    xlim([-1 1])
    ylim([-1 1])
    xlabel("Voltage In");
    ylabel("Voltage Out");
    set(gcf,'position',[0,0,imageSize,imageSize])
    hold on;
        yline(0, 'w'); xline(0, 'w');   
        plot(v_in, v_out, 'g');        
    hold off;
    plot_darkmode;

%% Geeky: y = x/sqrt(1 + x^2)

% Process voltage vector
for x = 1 : length(v_in)
    v_out(x) = v_in(x)/sqrt(1 + v_in(x)^2);
end

% Generate figure
figure
    xlim([-1 1])
    ylim([-1 1])
    xlabel("Voltage In");
    ylabel("Voltage Out");
    set(gcf,'position',[0,0,imageSize,imageSize])
    hold on;
        yline(0, 'w'); xline(0, 'w');   
        plot(v_in, v_out, 'r');         
    hold off;
    plot_darkmode;

%% SmolCronch: y = tanh(x)

% Process voltage vector
for x = 1 : length(v_in)
    v_out(x) = tanh(v_in(x));
end

% Generate figure
figure
    xlim([-1 1])
    ylim([-1 1])
    xlabel("Voltage In");
    ylabel("Voltage Out");
    set(gcf,'position',[0,0,imageSize,imageSize])
    hold on;
        yline(0, 'w'); xline(0, 'w');           
        plot(v_in, v_out, 'color', [171 104 87]./255);   
    hold off;
    plot_darkmode;

%% FatMan: y = (3/2)*x - (1/2)*x^3

% Process voltage vector
for x = 1 : length(v_in)
    if(v_in(x) < -1)
        v_out(x) = -1;
    elseif(v_in(x) > 1)
        v_out(x) = 1;
    else
        v_out(x) = (3/2)*v_in(x) - (1/2)*v_in(x)^3;
    end
end

% Generate figure
figure
    xlim([-1 1])
    ylim([-1 1])
    xlabel("Voltage In");
    ylabel("Voltage Out");
    set(gcf,'position',[0,0,imageSize,imageSize])
    hold on;
        yline(0, 'w'); xline(0, 'w');                
        plot(v_in, v_out, 'color', [0.4940 0.1840 0.5560]); 
    hold off;
    plot_darkmode;

%% Circle7: Line 6 Patent Equation

% Process voltage vector
for x = 1 : length(v_in)
    if(v_in(x) < -0.08905)
        v_out(x) = (-3/4)*( 1 - ( 1 - (abs(v_in(x)) - 0.032847))^12 ...
                    + (1/3)*(abs(v_in(x)) - 0.032847)) + 0.01;
    elseif(v_in(x) < 0.320018)
        v_out(x) = -6.153*v_in(x)^2 + 3.9375*v_in(x);
    else
        v_out(x) = 0.630035;
    end
end

% Generate figure
figure
    xlim([-1 1])
    ylim([-1 1])
    xlabel("Voltage In");
    ylabel("Voltage Out");
    set(gcf,'position',[0,0,imageSize,imageSize])
    hold on;
        yline(0, 'w'); xline(0, 'w');               
        plot(v_in, v_out, 'color', [0.9290 0.6940 0.1250]);
    hold off;
    plot_darkmode;

%% ForkInToaster: y = limit(-0.5, 5)

% Process voltage vector
for x = 1 : length(v_in)
    if(v_in(x) < -0.5)
        v_out(x) = -0.5;
    elseif(v_in(x) > 0.5)
        v_out(x) = 0.5;
    else
        v_out(x) = v_in(x);
    end
end

% Generate figure
figure
    xlim([-1 1])
    ylim([-1 1])
    xlabel("Voltage In");
    ylabel("Voltage Out");
    set(gcf,'position',[0,0,imageSize,imageSize])
    hold on;
        yline(0, 'w'); xline(0, 'w');
        plot(v_in, v_out, 'color', [0.3010 0.7450 0.9330]);
    hold off;
    plot_darkmode;

%% End