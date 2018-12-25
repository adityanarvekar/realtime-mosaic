# realtime-mosaic
Imaging devices have infiltrated every corner of modern life. They are omnipresent in multiple forms such as photographic cameras, security cameras, and mobile phones. Not only do these devices digitally document the life of the user, they also capture other individuals nearby. People can feel uncomfortable about losing control over their pictures, and there are serious privacy implications due to the massive publication of private pictures and other information along with them. Many face recognition systems have been built to automatically identify the face region on an image. However, none of them can achieve one hundred percent accuracy, especially when the face region has very low resolution or the image has poor quality. So to make sure privacy protection, it still requires necessary user’s manual input. For example, the Google street view, it still requires user’s editing to block all the passenger’s face.   In this project, you will implement an efficient and easy-to-use software tool to mask people’s face from camera video streams.
You will be requiring an opencv library installed in your PC.
I did this project as part of my coursework at University of Dayton in Advanced Interactive Media.
The requirements specified by our Professor are as follows :



Steps

(1) Load video from your laptop webcam by using OpenCV.

(2) The program allows user to select a target region via mouse button-down, dragging, and button up operations. The position where the mouse left button down occurs is recorded as the first corner of the rectangle region. Then the user holds the button and drags the mouse to a new location.  During the dragging, user can see a dynamic rectangle (e.g red color) rendered on the video, indicating user's selection (see Figure 1). After the user releases the left button, mosaic effect is generated permanently based on the user's selected rectangle region. The two diagonal corners of the rectangle region should locate at the positions where user's left-button-down and left-button up occur (see Figure 2).

                  

            Figure 1: during mouse dragging                                    Figure 2: after mouse left button up

(3) Pixels inside the rectangular region that defined by the user should be blurred with Mosaic effect. The level of blur depends on the user specified value. For example, you can use an integer variable to store it:

              int blur_degree = 5

Here “blur_degree” defines the length of each Mosaic unit square. By default it is 5 pixels in length. So the bigger of the “blur_degree”, the more blur of the selected region. Figure 3 shows a big value for the "blur_degree":



Figure 3. result of setting large value to the blur_degree.

(4) User can increase the blur level by hitting the keyboard key “i” or “I” and decrease the blur level by hitting the keyboard key “d” or “D”. The way of increasing or decreasing blur level follows the rule below:

a) Increasing Case: when “blur_degree” is less than 5, it increases by 1 each time when the key “i” or “I” is hit; when “blur_degree” is equal to or greater than 5, it increases by 5 each time when the key “i” or “I” is hit;

b) Decreasing Case: when the “blur_degree” is equal to or less than 5 but greater than 1, it decreases by 1 each time when the key “d” or “D” is hit; when “blur_degree” is greater than 5, it decreases by 5 each time when the key “d” or “D” is hit;

(5) During editing, user can remove the blur effect at any time by hitting the key “r” or “R”, just in case the region is not selected properly. Or user can also remove it by a single clicking left button.

(6) After the user finishes editing, the result image should be saved to a local drive with whatever filename by hitting the “s“ or “S” key.

 

Rubrics

(1) Correct Mouse Callback Functions (20%)

- To select a region on the image, three mouse operations (left-button-down, dragging, left button-up) are required. In your code, I should see some recording operations or variable updates after each mouse left click occurs.

- After the left-button-down, there should be nothing change on the image until the mouse starts being dragged. During dragging, a dynamic rectangle should be drawn on the image.

- After left-button-up, the selected region on the image should be changed with Mosaic blur effect.

 

(2) Correct Keyboard Callback Functions (10%)

- Press “i” or “I” key to increase the value of “blur_degree”, the selected image region

becomes more blurred.

- Press “d” or “D” key to decrease the value of “blur_degree”, the selected image region

becomes less blurred.

- Press “s” or “S” key to save the result image into a local file.

- Press “r” or “R” key to remove the current editing results and return to the original image.

 

(3) Correct Mosaic effect on selected pixels (40%)

- This is the main part of this assignment. You should use pixel-wise manipulation to modify the image as we discussed in class. You are not allowed to call any well-defined library or builtin functions to do the bur.  Since the selected region may not be always dividable by the "blur_degree", there could be a margin the blocks inside the region are blurred.

 

(4) Multiple Blur Regions  (30%)

- Your code allows users to select multiple regions for blurring. For example, if there are two areas in the video need to be blurred. Users can select two regions on the window. Then the two regions corresponding contents should be blurred. To simplify the problem, when user use the keyboard to adjust the size of the block. You can let all the blur regions have their "blur_degree" change simultaneously. 

 

Submission

Your project code should be submitted through Isidore online. Suggested materials:

(1) Code file or Source files Only (“.h” or “.c” or “.hpp” or “.cpp”)

Your code files should be in one or some of the above format. If you have more than one files, put them into a folder and compress them in “.zip” or “.rar” format. I do not suggest to submit the whole project as the library files and backup files are usually large.

(2) Document file (“.pdf” or “.doc” or “.docx”)

Provide a simple document including:

- Your resulting images (no more than 10 images, you can include some other images)

- If your project requires special configuration or additional header files, please provide a short paragraph describing it.
